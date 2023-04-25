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
    user* realPlayer;


//    QLabel score;
    int flag;




public:
    //RealGame(int level , user* user);
    RealGame(int level, user* realPlayer);
    void keyPressEvent(QKeyEvent *event);
    void  constantElementDisplay();
    void  displaygameOver();


};

#endif // REALGAME_H


