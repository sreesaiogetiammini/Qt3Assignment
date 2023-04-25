#ifndef PLAYERSCENE_H
#define PLAYERSCENE_H

#pragma once
#include "signupscene.h"
#include <QTableWidget>
class PlayerScene : public QGraphicsScene
{
public:
    PlayerScene();
    void constantElementDisplay();
    void  displayBirthDayGreeting();
    void setFirstScreenQPushButtonProperties(QPushButton *button);




public:
    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;


    QLabel* welcomePlayerL;
    QLabel* profilePicLabel;
    QString* profilePicFileName;
    QPushButton *Easy;
    QPushButton *Medium;
    QPushButton *Hard;
    QPushButton *mainMenu;
    QDialogButtonBox *playerPageButtonBox;
    QGraphicsProxyWidget *playerProxyWidget;
    QWidget *playerWidget;
    QPushButton *closeBirthdayButton;
     QGraphicsProxyWidget *birthdayProxyWidget;

};

#endif // PLAYERSCENE_H
