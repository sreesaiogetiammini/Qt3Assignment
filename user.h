#ifndef USER_H
#define USER_H


#pragma once
#include "headers.h"

class user
{
public:
    user(QString username);
    void signup(QString &username, QString &password, QString &firstname, QString &lastname, QString &dob, QString &filename);
    bool login(QString &username, QString &password);
    struct scoreStruct {
        int score;
        QString date;
        QString level;
    };
    QVector<scoreStruct> scores;
    void updateScore(int score, int level);
    void deleteUser();
    QString username;
    QDate dob;
    bool isBirth;
    bool isBirthday();
    QJsonObject userObject;
    QJsonValue QVectorToJsonValue(const QVector<scoreStruct>& scores);

    QVector<scoreStruct> getScores(QString username);

    QVector<scoreStruct> JsonValueToQVector(const QJsonValue &jsonValue);

    struct globalScore{
        QString username;
        int highScore;
    };

//    QVector<globalScore> getGlobalScores();


private:
    void saveDataToJson();
    void loadDataFromJson();
public:
    QJsonArray usersArray;
//    QString username;
};



#endif // USER_H
