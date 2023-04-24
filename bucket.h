#ifndef BUCKET_H
#define BUCKET_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>


class bucket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    bucket(QGraphicsItem *parent = nullptr);
};
#endif // BUCKET_H
