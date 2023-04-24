#ifndef SIGNUPSCENE_H
#define SIGNUPSCENE_H

#pragma once
#include <QQuickItem>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QGraphicsScene>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>
#include <QString>
#include "bucket.h"
#include "firstscreen.h"
#include "passwordValidator.h"
#include "ageValidator.h"
#include <QValidator>
#include <QRegularExpressionValidator>
#include "user.h"

class SignUpScene: public QGraphicsScene
{
public:
    SignUpScene();
    void  constantElementDisplay();
    void setFirstScreenQPushButtonProperties(QPushButton* button);
    void chooseProfilePic();
    void submitButtonClicked();
     void resetButtonClicked();
    void updateButtonState(QLineEdit* lineEdit);
    bool isPasswordValid(const QString& password);

public:

    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;


    QLabel* firstNameL;
    QLabel* lastNameL;
    QLabel* dobL;
    QLabel* genderL;
    QLabel* userNameL;
    QLabel* setPasswordL;
    QLabel* confirmPasswordL;
    QLabel *errorLabel;

    QLineEdit* firstNameLE;
    QLineEdit* lastNameLE;
    QLineEdit* userNameLE;
    QLineEdit* setPasswordLE;
    QLineEdit* confirmPasswordLE;
    QCalendarWidget *doBcalendar;

    QGroupBox* genderGB;
    QVBoxLayout* genderLayout;
    QRadioButton* maleRB;
    QRadioButton* femaleRB;
    QGraphicsProxyWidget *signUpProxyWidget;
    QWidget *signUpWidget;


    QPushButton *reset;
    QPushButton *submit;
    QPushButton *mainMenu;
    QDialogButtonBox *signUpPageButtonBox;
    QLabel *profilePicLabel;
    QPushButton *choosePicButton;

};

#endif // SIGNUPSCENE_H
