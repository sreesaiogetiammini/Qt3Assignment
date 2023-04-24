#include "user.h"
#include <QJsonObject>
#include <QFile>
#include <QCoreApplication>


user :: user (){
    loadDataFromJson();

}

void user::signup(QString &username, QString &password, QString &firstname, QString &lastname, QString &dob){
    QJsonObject userData;
    userData["firstname"] = firstname;
    userData["lastname"] = lastname;
    userData["username"] = username;
    userData["password"] = password;
    userData["dob"] = dob;
    QJsonArray scoresJson;
    for (const int& value : scores)
    {
        scoresJson.append(value);
    }
    userData["scores"] = scoresJson;

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
                        if (jsonValue.isDouble()) // You can also use other value types, depending on your JSON data
                        {
                            scores.append(jsonValue.toInt());
                        }
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


void user :: updateScore(int score){
    scores.append(score);
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    while(scores.size() > 10){
        scores.pop_back();
    }
}

