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
    struct scoreStruct {
        int score;
        QDate date;
        int level;
    };

    QVector<scoreStruct> scores;
    void updateScore(int score, int level);


private:
    void saveDataToJson();
    void loadDataFromJson();
    QJsonArray usersArray;
};



#endif // USER_H
