#ifndef SIGNUPSCENE_H
#define SIGNUPSCENE_H

#pragma once
#include "headers.h"

class SignUpScene: public QGraphicsScene
{
public:
    SignUpScene();
    void  constantElementDisplay();
    void setFirstScreenQPushButtonProperties(QPushButton* button);
    void chooseProfilePic();
    void submitButtonClicked();
    void resetButtonClicked();
    void mainMenuButtonClicked();
    bool FirstNameLastNameValidatons();
    bool DateOfBirthValidations();
    bool passwordValidation();
    bool userNameValidations();
    void updateButtonState(QLineEdit* lineEdit);

public:

    QWidget *backgroundItem;
    QTimer *timer;
    bucket *bucketImg;
    QPushButton *MusicOn;
    QPushButton *MusicOff;
    QGraphicsProxyWidget *musicButtonsProxyWidget;
    QMediaPlayer* player ;
    QAudioOutput *audioOutput;


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
    QLabel *passwordLabel;
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
