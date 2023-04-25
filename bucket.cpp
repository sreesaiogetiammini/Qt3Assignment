#pragma once
#include "bucket.h"
#include "gameOverImage.h"

bucket::bucket(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    // set the image of the bucket
    setPixmap(QPixmap(":/bucket.png").scaled(200,200));
    setPos(500, 700);
    scoreLabel = new QLabel;
    QFont font("Arial", 40);
    scoreLabel->setText("Misses: 0");
    scoreLabel->setFont(font);
    scoreLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    scoreLabel->setGeometry(50, 50, 200, 100);
    scoreLabel->setStyleSheet("QLabel { background-color : rgba(255, 255, 255, 50); border-radius: 5px; padding: 5px; color : black; width:50px; height:50px}");
//    scene() -> addWidget(scoreLabel);
}

bucket :: bucket(user* realPlayer){
//    qInfo() << "in bucket ";
//    qInfo() << realPlayer -> username;
    this -> realPlayer = realPlayer;
    setPixmap(QPixmap(":/bucket.png").scaled(200,200));
    setPos(500, 700);
    scoreLabel = new QLabel;
    QFont font("Arial", 40);
    scoreLabel->setText("Misses: 0");
    scoreLabel->setFont(font);
    scoreLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    scoreLabel->setGeometry(50, 50, 200, 100);
    scoreLabel->setStyleSheet("QLabel { background-color : rgba(255, 255, 255, 50); border-radius: 5px; padding: 5px; color : black; width:50px; height:50px}");
}

void bucket :: increaseScore() {
    score++;

}

void bucket :: countMiss (){
    misses++;
    scoreLabel->setText("Misses: " + QString::number(misses));
    scoreLabel->setStyleSheet("QLabel { background-color : red; border-radius: 5px; padding: 5px; color : black; width:50px; height:50px}");
    if(misses == 10){
        realPlayer -> updateScore(score, 2);
    }
}


