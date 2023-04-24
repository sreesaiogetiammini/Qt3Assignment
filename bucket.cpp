#include "bucket.h"

bucket::bucket(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    // set the image of the bucket
    setPixmap(QPixmap(":/bucket.png").scaled(200,200));
    setPos(500, 700);
}

void bucket :: increaseScore() {
    score++;
}

void bucket :: countMiss (){
    misses++;
}


