#ifndef REALGAME_H
#define REALGAME_H

#pragma once
#include "headers.h"
#include "bucket.h"
#include "gameOverImage.h"
#include "clouds.h"
#include "water.h"
#include "imageWidget.h"
#include "user.h"

class RealGame : public QGraphicsScene
{

public:
    QWidget *backgroundItem;
    QTimer *timer;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;
    QMediaPlayer* player ;
    QAudioOutput *audioOutput;
    bucket *bucketImg;
    QGraphicsProxyWidget *gameOverProxyWidget;
    QPushButton *backButton;
    user* realPlayer;



//    QLabel score;
    int flag;



public slots:
void  displaygameOver();
void backbuttonClicked();

public:
    //RealGame(int level , user* user);
    RealGame(int level, user* realPlayer);
    void keyPressEvent(QKeyEvent *event);
    void  constantElementDisplay();



};

#endif // REALGAME_H


