#include "water.h"

#include "water.h"
#include <QGraphicsScene>

water::water()
{
    setPixmap((QPixmap(":/water.gif")).scaled(30,30));
    timer_drop = new QTimer();
    connect(timer_drop, &QTimer::timeout, this, &water::move_droplet);
    timer_drop->start(1000);
}

void water::move_droplet()
{
    setPos(x(), y()+10);
    if (y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
