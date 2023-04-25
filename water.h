#ifndef WATER_H
#define WATER_H


#pragma once
#include "headers.h"

class water : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    water(bucket *bucket1, int level);

public slots:
    void move_droplet();

private:
    QTimer *timer_drop;
    bucket *newBucket;
};


#endif // WATER_H
