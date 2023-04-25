#ifndef GAMESCENE_H
#define GAMESCENE_H

#pragma once
#include "headers.h"

class GameScene : public QGraphicsScene
{
public:
    GameScene();

public:
    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;

public:
    void  constantElementDisplay();
};

#endif // GAMESCENE_H
