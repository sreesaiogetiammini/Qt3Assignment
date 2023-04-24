#ifndef GAMESCENE_H
#define GAMESCENE_H

#pragma once
#include <QQuickItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QCalendarWidget>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QGraphicsProxyWidget>
#include "bucket.h"

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
