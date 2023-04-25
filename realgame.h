#ifndef REALGAME_H
#define REALGAME_H

#include <QQuickItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "signupscene.h"
#include "bucket.h"
#include "water.h"
#include "clouds.h"

class RealGame : public QGraphicsScene
{

public:
    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;
//    QLabel score;
    int flag;




public:
    //RealGame(int level ,QDate date, user* user);
    RealGame(int level);
    void keyPressEvent(QKeyEvent *event);
    void  constantElementDisplay();
public slots:
};

#endif // REALGAME_H


