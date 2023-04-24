#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#pragma once
#include <QQuickItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QCalendarWidget>
#include "bucket.h"
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QGraphicsProxyWidget>
#include <QFont>
#include <QColor>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>
#include <QLinearGradient>
#include <QGraphicsView>

class FirstScreen : public QGraphicsScene
{
public:
    FirstScreen();

public:
    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QGraphicsTextItem* gameName;
    QDialogButtonBox* buttonBox;
    QPushButton *SignUp;
    QPushButton *SignIn;
    QPushButton *GuestPlay;
    QPushButton *Exit;
    QGraphicsProxyWidget *buttonProxyWidget;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;

signals:
    void sceneSwitched(QGraphicsScene *scene);

public:
    void  constantElementDisplay();
    void setFirstScreenQPushButtonProperties(QPushButton* button);
public slots:
    void signUpButtonClick();
    void signInButtonClick();
    void exitButtonClick();
    void guestGameButtonClick();

};

#endif // FIRSTSCREEN_H
