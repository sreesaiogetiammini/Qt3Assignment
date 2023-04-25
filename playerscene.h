#ifndef PLAYERSCENE_H
#define PLAYERSCENE_H

#pragma once
#include "headers.h"

class PlayerScene : public QGraphicsScene
{
public:
    PlayerScene(user* player);
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
    QMediaPlayer* player ;
    QAudioOutput *audioOutput;

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
