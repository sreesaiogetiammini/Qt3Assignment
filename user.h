#ifndef USER_H
#define USER_H


#pragma once
#include "headers.h"

class user
{
public:
    user(QString username);
    void signup(QString &username, QString &password, QString &firstname, QString &lastname, QString &dob);
    bool login(QString &username, QString &password);
    struct scoreStruct {
        int score;
        QDate date;
        QString level;
    };

    QVector<scoreStruct> scores;
    void updateScore(int score, int level);
    void deleteUser();
    QString username;


private:
    void saveDataToJson();
    void loadDataFromJson();
public:
    QJsonArray usersArray;
};



#endif // USER_H
