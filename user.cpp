#pragma once
#include "headers.h"
#include "user.h"



user :: user (){
    loadDataFromJson();
    scores = QVector<scoreStruct>();
}

void user::signup(QString &username, QString &password, QString &firstname, QString &lastname, QString &dob){
    QJsonObject userData;
    userData["firstname"] = firstname;
    userData["lastname"] = lastname;
    userData["username"] = username;
    userData["password"] = password;
    userData["dob"] = dob;
//    QJsonArray scoresJson;
//    for (const int& value : scores)
//    {
//        scoresJson.append(value);
//    }
//    userData["scores"] = scoresJson;

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
                    QJsonArray jsonArray = userObject["scores"].toArray();
                    for (const QJsonValue& jsonValue : jsonArray)
                    {

//                            scores.append(jsonValue.toInt());
                            scoreStruct newScore;
                            QJsonObject scoreObject = jsonValue.toObject();
                            newScore.score = scoreObject["score"].toInt();
                            newScore.date = QDate::fromString(scoreObject["date"].toString(), "yyyy-MM-dd");
                           // newScore.level = scoreObject["level"].toString();
                    }
                }
                return true;
            }

        }
    }
    return false;
}

void user :: saveDataToJson(){
    QJsonDocument jsonDocument;
    qInfo() << usersArray;
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

    if(level == 1) newScore.level = "easy";
    else if(level == 2) newScore.level = "medium";
    else newScore.level = "hard";

    newScore.date = QDate::currentDate();

    scores.append(newScore);
    std::stable_sort(scores.begin(), scores.end(),
                     [](const scoreStruct& s1, const scoreStruct& s2) {
                         return s1.date < s2.date;
                     });


//    std::sort(scores.begin(), scores.end(), std::greater<int>());

    while(scores.size() > 10){
        scores.pop_back();
    }
}

