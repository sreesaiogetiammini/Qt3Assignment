#ifndef SIGNINSCENE_H
#define SIGNINSCENE_H

#pragma once
#include "headers.h"

class SignInScene : public QGraphicsScene
{
public:
    SignInScene();
    void  constantElementDisplay();
    void setFirstScreenQPushButtonProperties(QPushButton* button);
    void chooseProfilePic();
    void loginButtonClicked();
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
    QMediaPlayer* player ;
    QAudioOutput *audioOutput;

    QLabel* userNameL;
    QLabel* PasswordL;
    QLabel *errorLabel;
    QLineEdit* userNameLE;
    QLineEdit* PasswordLE;


    QGraphicsProxyWidget *signInProxyWidget;
    QWidget *signInWidget;
    QPushButton *mainmenu;
    QPushButton *reset;
    QPushButton *login;
    QDialogButtonBox *signInPageButtonBox;

};

#endif // SIGNINSCENE_H
