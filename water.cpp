
#pragma once
#include "headers.h"
#include "water.h"
#include "gameOverImage.h"

water::water(bucket* bucket1, int level)
{
    newBucket = bucket1;
    setPixmap((QPixmap(":/water.gif")).scaled(30,30));
    timer_drop = new QTimer();
    connect(timer_drop, &QTimer::timeout, this, &water::move_droplet);
    timer_drop->start(100 * level);
}

void water::move_droplet()
{
    setPos(x(), y()+10);
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    foreach (QGraphicsItem* item, collidingItemsList) {
        // Check if the colliding item is the bucket
        if (dynamic_cast<bucket*>(item)) {
            // Removing the droplet from the scene
            scene()->removeItem(this);
            // add score
            newBucket->increaseScore();
            qInfo() << newBucket -> score;
            delete this;
            return;
        }
    }

    if (y() > scene()->height()) {
        scene()->removeItem(this);
        newBucket -> countMiss();
        delete this;
        return;
    }
}
