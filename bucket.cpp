#pragma once
#include "bucket.h"

bucket::bucket(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    // set the image of the bucket
    setPixmap(QPixmap(":/bucket.png").scaled(200,200));
    setPos(500, 700);
    scoreLabel = new QLabel;
    scoreLabel->setText("Misses: 0");
    scoreLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    scoreLabel->setStyleSheet("QLabel { background-color : rgba(255, 255, 255, 50); border-radius: 5px; padding: 5px; color : black; width:50px; height:50px}");
//    scene() -> addWidget(scoreLabel);
}

void bucket :: increaseScore() {
    score++;

}

void bucket :: countMiss (){
    misses++;
    scoreLabel->setText("Misses: " + QString::number(misses));
    if(misses == 10){
        delete this;
    }
}


