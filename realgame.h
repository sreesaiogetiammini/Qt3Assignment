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
    QGraphicsProxyWidget *gameOverProxyWidget;
    QPushButton *backButton;

//    QLabel score;
    int flag;



public slots:
void  displaygameOver();
void backbuttonClicked();

public:
    //RealGame(int level , user* user);
    RealGame(int level);
    void keyPressEvent(QKeyEvent *event);
    void  constantElementDisplay();



};

#endif // REALGAME_H


