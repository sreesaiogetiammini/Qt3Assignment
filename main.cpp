#pragma once
#include "headers.h"
#include "firstscreen.h"
#include "signupscene.h"
#include "signinscene.h"
#include "playerscene.h"
#include "realgame.h"
#include "user.h"
#include <iostream>

enum difficulty {
    easy = 3,
    medium = 2,
    hard = 1
};

int main(int argc , char** argv){

    qreal screenHeight = 1400;
    qreal screenWidth = 900;
    QApplication app(argc,argv);

    FirstScreen* firstScreen = new FirstScreen();
    SignUpScene* signupScene = new SignUpScene();
    SignInScene* signinScene = new SignInScene();
    QString user2 = "user";
    user* guest = new user("");
    user* loginUser = new user("krishna11");
    PlayerScene* guestPlayerScene = new PlayerScene(guest);
    PlayerScene* playerScene = new PlayerScene(loginUser);


    QGraphicsView* view = new QGraphicsView();
    view->setScene(firstScreen);


    // Create a button to switch to scene2
    QPushButton* signUpSwitchButton = firstScreen->SignUp;
    QPushButton* signInSwitchButton = firstScreen->SignIn;
    QPushButton* guestSwitchButton = firstScreen->GuestPlay;

    QPushButton* signUpMainButton = signupScene->mainMenu;
    QPushButton* signInMainButton = signinScene->mainmenu;
    QPushButton* guestMainButton = playerScene->mainMenu;




    QPushButton* loginButton = signinScene->login;


    // Connect the button to a slot that switches the scene
    QObject::connect(signUpSwitchButton, &QPushButton::clicked, [=]() {
      view->setScene(signupScene);

    });

    QObject::connect(signInSwitchButton, &QPushButton::clicked, [=]() {

        view->setScene(signinScene);

    });

    QObject::connect(guestSwitchButton, &QPushButton::clicked, [=]() {
        view->setScene(playerScene);
    });

    QObject::connect(loginButton, &QPushButton::clicked, [=]() {
        QString userName = signinScene->userNameLE->text();
        QString password = signinScene->PasswordLE->text();
        user* loginUser = new user(userName);
        if(loginUser->login(userName,password)){
            view->setScene(playerScene);
        }
        else{
            view->setScene(signinScene);
        }

    });

     // Connect the button to a slot that switches the scene
     QObject::connect(signUpMainButton, &QPushButton::clicked, [=]() {
        view->setScene(firstScreen);
     });

    // Connect the button to a slot that switches the scene
    QObject::connect(guestMainButton, &QPushButton::clicked, [=]() {
        view->setScene(firstScreen);
    });

     // Connect the button to a slot that switches the scene
     QObject::connect(signInMainButton, &QPushButton::clicked, [=]() {
         view->setScene(firstScreen);
     });


     QPushButton* easyGameButton = playerScene->Easy;
     QPushButton* mediumGameButton = playerScene->Medium;
     QPushButton* hardGameButton = playerScene->Hard;

     // Connect the button to a slot that switches the scene
     QObject::connect(easyGameButton, &QPushButton::clicked, [=]() {
         difficulty level = easy;
          RealGame* realgameScene = new RealGame(level);
         view->setScene(realgameScene);
     });
     QObject::connect(mediumGameButton, &QPushButton::clicked, [=]() {
         difficulty level = medium;
         RealGame* realgameScene = new RealGame(level);
         view->setScene(realgameScene);
     });
     QObject::connect(hardGameButton, &QPushButton::clicked, [=]() {
         difficulty level = hard;
         RealGame* realgameScene = new RealGame(level);
         view->setScene(realgameScene);
     });


    // Set the fixed size of the view
    view->setFixedSize(screenHeight, screenWidth);
    // Prevent scroll bars from appearing
    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    // Show the view
    view->show();




    return app.exec();
}
