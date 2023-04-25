#ifndef USER_H
#define USER_H


#pragma once
#include "headers.h"
#include "user.h"

class user
{
public:
    user();
    void signup(QString &username, QString &password, QString &firstname, QString &lastname, QString &dob);
    bool login(QString &username, QString &password);
    struct scoreStruct {
        int score;
        QDate date;
        QString level;
    };
    QVector<scoreStruct> scores;
    void updateScore(int score, int level);


private:
    void saveDataToJson();
    void loadDataFromJson();
public:
    QJsonArray usersArray;
    QString username;
};



#endif // USER_H
