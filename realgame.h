#ifndef REALGAME_H
#define REALGAME_H

#pragma once
#include "headers.h"

class RealGame : public QGraphicsScene
{

public:
    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;
    QMediaPlayer* player ;
    QAudioOutput *audioOutput;



//    QLabel score;
    int flag;




public:
    //RealGame(int level , user* user);
    RealGame(int level);
    void keyPressEvent(QKeyEvent *event);
    void  constantElementDisplay();
public slots:
};

#endif // REALGAME_H


