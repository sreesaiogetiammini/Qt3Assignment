#pragma once
#include "headers.h"
#include "user.h"



user :: user (QString username){
    scores = QVector<scoreStruct>();
    loadDataFromJson();
    this -> username = username;
}

void user::signup(QString &username, QString &password, QString &firstname, QString &lastname, QString &dob, QString &filename){
    QJsonObject userData;
    userData["firstname"] = firstname;
    userData["lastname"] = lastname;
    userData["username"] = username;
    userData["password"] = password;
    userData["dob"] = dob;
    userData["filename"] = filename;
    qInfo() << filename;
    userData["scores"] = {};
    usersArray.append(userData);
    qInfo() << "data appended to array";
    saveDataToJson();
}

bool user :: login(QString &username, QString &password){
    foreach (const QJsonValue &value, usersArray)
    {
        if (value.isObject())
        {
            QJsonObject userObject = value.toObject();
            if (userObject["username"].toString() == username &&
                userObject["password"].toString() == password){
                if(userObject["scores"].isArray()){
                    this -> dob = QDate::fromString(userObject["dob"].toString(), "dd-MM-yyyy");
                    QJsonArray jsonArray = userObject["scores"].toArray();
                    for (const QJsonValue& jsonValue : jsonArray)
                    {
                            scoreStruct newScore;
                            QJsonObject scoreObject = jsonValue.toObject();
                            newScore.score = scoreObject["score"].toInt();
                            newScore.date = scoreObject["date"].toString();
                            newScore.level = scoreObject["level"].toString();
                            scores.append(newScore);
                    }
                }
                qInfo() << scores.size();
                return true;
            }

        }
    }
    return false;
}

void user :: saveDataToJson(){
    QJsonDocument jsonDocument;
    jsonDocument.setArray(usersArray);
    QByteArray bytes = jsonDocument.toJson( QJsonDocument::Indented );

    QString path = QCoreApplication::applicationDirPath();

    QFile file(path + "/users.json");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file); // Use QTextStream for writing text
        stream << bytes; // Write JSON data with Compact format
        qInfo() << "data written to file";
        stream.flush();
        file.close();
        qDebug() << "Data saved to users.json";
    } else {
        qDebug() << "Data not saved to users.json";
    }
}


void user :: loadDataFromJson(){

    QFile file("users.json");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
        usersArray = jsonDocument.array();
        file.close();
    }

}


void user :: updateScore(int score, int level){
//    scores.append(score);
    scoreStruct newScore;
    newScore.score = score;

    if(level == 3) newScore.level = "easy";
    else if(level == 2) newScore.level = "medium";
    else newScore.level = "hard";
    newScore.date = QDate::currentDate().toString("yyyy-MM-dd");
    scores.append(newScore);
    std::stable_sort(scores.begin(), scores.end(),
                     [](const scoreStruct& s1, const scoreStruct& s2) {
                         return s1.date < s2.date;
                     });


//    std::sort(scores.begin(), scores.end(), std::greater<int>());

    while(scores.size() > 10){
        scores.pop_back();
    }
// QJsonValueRef jsonValue : usersArray
    for (int i = 0; i < usersArray.size(); i++) {
        if (usersArray[i].toObject()["username"] == this -> username) {
            // Update the value
            QJsonObject userObject = usersArray[i].toObject();
            userObject.insert("scores", QVectorToJsonValue(scores));
            usersArray[i] = userObject;
            qInfo() << "for loopppppppp";
            qInfo() << QVectorToJsonValue(scores);
            break;
        }
    }

    saveDataToJson();
    loadDataFromJson();
    qInfo() << usersArray;
}

void user :: deleteUser(){
    QFile file("users.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open users.json";
        return;
    }

    QByteArray userData = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData);
    QJsonArray usersArray = jsonDoc.array();

    // Iterate through the users and remove the user with matching username
    for (int i = 0; i < usersArray.size(); ++i) {
        QJsonObject user = usersArray.at(i).toObject();
        QString storedUsername = user["username"].toString();
        if (storedUsername == username) {
            usersArray.removeAt(i);
            file.resize(0);
            file.write(jsonDoc.toJson());
            file.close();
            return;
        }
    }
}

bool user :: isBirthday(){
    for (int i = 0; i < usersArray.size(); i++) {

        if (usersArray[i].toObject()["username"] == username) {
            // Update the value
           QDate dobUser =  QDate::fromString(usersArray[i].toObject()["dob"].toString(), "dd-MM-yyyy");
           QDate currentDate = QDate::currentDate();
           return dobUser.month() == currentDate.month() && dobUser.day() == currentDate.day();
        }
    }
  return false;
}

QJsonValue user :: QVectorToJsonValue(const QVector<scoreStruct>& scores)
{
    QJsonArray jsonArray;

    for (const scoreStruct& score : scores) {
        QJsonObject jsonObject;
        //jsonObject["date"] = score.date.toString();
         jsonObject["date"] = score.date;
        jsonObject["level"] = score.level;
        jsonObject["score"] = score.score;
        jsonArray.append(jsonObject);
    }

    return QJsonValue::fromVariant(jsonArray.toVariantList());
}

QVector<user::scoreStruct> user :: getScores(QString username){
    for (int i = 0; i < usersArray.size(); i++) {

        if (usersArray[i].toObject()["username"] == username) {
            // Update the value
            return JsonValueToQVector(usersArray[i].toObject()["scores"]);;
        }
    }
    return scores;
}

QVector<user::scoreStruct> user :: JsonValueToQVector(const QJsonValue &jsonValue) {
    QVector<scoreStruct> scores;
    if (jsonValue.isArray()) {
        QJsonArray jsonArray = jsonValue.toArray();
        for (const QJsonValue &jsonScore : jsonArray) {
            if (jsonScore.isObject()) {
                scoreStruct newscore;
                QJsonObject jsonScoreObject = jsonScore.toObject();
                newscore.date = jsonScoreObject["date"].toString();
                newscore.score = jsonScoreObject.value("score").toInt();
                newscore.level = jsonScoreObject.value("level").toString();
                scores.append(newscore);
            } else {
                qInfo() << "is not an object";
            }
        }
    }
    return scores;
}
