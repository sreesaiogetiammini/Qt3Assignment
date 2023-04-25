#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#pragma once
#include "headers.h"

class FirstScreen : public QGraphicsScene
{
public:
    FirstScreen();

public:
    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QGraphicsTextItem* gameName;
    QDialogButtonBox* buttonBox;
    QPushButton *SignUp;
    QPushButton *SignIn;
    QPushButton *GuestPlay;
    QPushButton *Exit;
    QGraphicsProxyWidget *buttonProxyWidget;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;
    QMediaPlayer* player ;
    QAudioOutput *audioOutput;

signals:
    void sceneSwitched(QGraphicsScene *scene);

public:
    void constantElementDisplay();
    void setFirstScreenQPushButtonProperties(QPushButton* button);
public slots:
    void signUpButtonClick();
    void signInButtonClick();
    void exitButtonClick();
    void guestGameButtonClick();


};

#endif // FIRSTSCREEN_H
