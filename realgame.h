#ifndef REALGAME_H
#define REALGAME_H

#pragma once
#include "headers.h"
#include "bucket.h"
#include "gameOverImage.h"
#include "clouds.h"
#include "water.h"
#include "imageWidget.h"

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


//    QLabel score;
    int flag;




public:
    //RealGame(int level , user* user);
    RealGame(int level);
    void keyPressEvent(QKeyEvent *event);
    void  constantElementDisplay();
    void  displaygameOver();


};

#endif // REALGAME_H


