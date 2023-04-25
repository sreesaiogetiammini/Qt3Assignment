#ifndef GAMEOVERIMAGE_H
#define GAMEOVERIMAGE_H

#include "headers.h"

class gameOver : public QWidget {
public:
    gameOver(QWidget *parent = nullptr ) : QWidget(parent) {
        QHBoxLayout *layout = new QHBoxLayout(this);
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(QPixmap(":/gameover.png").scaledToWidth(700).scaledToHeight(500)); // replace with your image path
        layout->addWidget(imageLabel);
        QPushButton *closeButton = new QPushButton("Back", this);
        layout->addWidget(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
};


#endif // GAMEOVERIMAGE_H
