#ifndef CLOUDS_H
#define CLOUDS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Clouds : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Clouds(QObject *parent = nullptr);

public slots:
    void move();

private:
    QTimer *timer;
};

#endif // CLOUDS_H
