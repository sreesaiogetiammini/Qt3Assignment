#ifndef BUCKET_H
#define BUCKET_H


#include "QtWidgets/qlabel.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>


class bucket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

signals:
    void missesReachedTen();

public slots:
    void updateMisses() {
        if (misses == 2) {
            emit missesReachedTen();
        }
    }

public:
    bucket(QGraphicsItem *parent = nullptr);
    QLabel* scoreLabel;
    int score = 0;
    int misses = 0;
    void increaseScore();
    void countMiss();
};
#endif // BUCKET_H
