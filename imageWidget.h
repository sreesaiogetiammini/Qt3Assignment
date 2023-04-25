#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H
#include<QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QWidget>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class ImageWidget : public QWidget {
public:
    ImageWidget(QWidget *parent = nullptr) : QWidget(parent) {
        QHBoxLayout *layout = new QHBoxLayout(this);
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(QPixmap(":/birthday.png").scaledToWidth(700).scaledToHeight(500)); // replace with your image path
        layout->addWidget(imageLabel);
        QPushButton *closeButton = new QPushButton("Close", this);
        layout->addWidget(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
};

#endif // IMAGEWIDGET_H
