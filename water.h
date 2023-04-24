#ifndef WATER_H
#define WATER_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class water : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    water();

public slots:
    void move_droplet();

private:
    QTimer *timer_drop;
};


#endif // WATER_H
