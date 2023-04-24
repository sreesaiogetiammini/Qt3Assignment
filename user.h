#ifndef USER_H
#define USER_H
#include <QString>
#include <QDate>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class user
{
public:
    user();

    void signup(QString &username, QString &password, QString &firstname, QString &lastname, QString &dob);
    bool login(QString &username, QString &password);
    QVector<int> scores;
    void updateScore(int score);


private:
    void saveDataToJson();
    void loadDataFromJson();
    QJsonArray usersArray;
};



#endif // USER_H
