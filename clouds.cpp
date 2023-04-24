#include "clouds.h"

Clouds::Clouds(QObject *parent) : QObject(parent), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/cloud.png").scaled(70,50));
    setPos(0, 0);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(7);
}

void Clouds::move()
{
    setPos(x() + 1, y());
    if (x() > 1080) {
        setPos(-pixmap().width(), y());
    }
}
