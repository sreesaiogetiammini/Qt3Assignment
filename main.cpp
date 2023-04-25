#pragma once
#include "headers.h"
#include "firstscreen.h"
#include "signupscene.h"
#include "signinscene.h"
#include "playerscene.h"
#include "realgame.h"
#include "user.h"
#include <iostream>
#include "bucket.h"

enum difficulty {
    easy = 3,
    medium = 2,
    hard = 1
};

user* guest ;
user* player;
PlayerScene* playerScene;

int main(int argc , char** argv){

    qreal screenHeight = 1400;
    qreal screenWidth = 900;
    QApplication app(argc,argv);


    FirstScreen* firstScreen = new FirstScreen();
    SignUpScene* signupScene = new SignUpScene();
    SignInScene* signinScene = new SignInScene();


    // Create a button to switch to scene2
    QPushButton* signUpSwitchButton = firstScreen->SignUp;
    QPushButton* signInSwitchButton = firstScreen->SignIn;
    QPushButton* guestSwitchButton = firstScreen->GuestPlay;


    QPushButton* signUpMainButton = signupScene->mainMenu;
    QPushButton* signInMainButton = signinScene->mainmenu;

//    difficulty hardLevel = hard;
//    RealGame *realgameScene = new RealGame(hardLevel,guest);
//    QPushButton* gameBackButton =  realgameScene->backButton;

    QGraphicsView* view = new QGraphicsView();
    view->setScene(firstScreen);


    QPushButton* loginButton = signinScene->login;

    // Connect the button to a slot that switches the scene
    QObject::connect(signUpMainButton, &QPushButton::clicked, [=]() {
        view->setScene(firstScreen);
    });

  ;

    // Connect the button to a slot that switches the scene
    QObject::connect(signInMainButton, &QPushButton::clicked, [=]() {
        view->setScene(firstScreen);
    });


    // Connect the button to a slot that switches the scene
    QObject::connect(signUpSwitchButton, &QPushButton::clicked, [=]() {
      view->setScene(signupScene);

    });

    QObject::connect(signInSwitchButton, &QPushButton::clicked, [=]() {
          view->setScene(signinScene);

    });

    QObject::connect(guestSwitchButton, &QPushButton::clicked, [=]() {
        player = new user("");
        playerScene = new PlayerScene(player);
        view->setScene(playerScene);
        QPushButton* easyGameButton = playerScene->Easy;
        QPushButton* mediumGameButton = playerScene->Medium;
        QPushButton* hardGameButton = playerScene->Hard;
        QPushButton* guestMainButton = playerScene->mainMenu;
        // Connect the button to a slot that switches the scene
        QObject::connect(easyGameButton, &QPushButton::clicked, [=]() {
            difficulty level = easy;
            RealGame* realgameScene = new RealGame(level, player);
            view->setScene(realgameScene);
            QPushButton* backButton = realgameScene->backButton;
            QObject::connect(backButton, &QPushButton::clicked, [=]() {
                view->setScene(playerScene);
            });
        });
        QObject::connect(mediumGameButton, &QPushButton::clicked, [=]() {
            difficulty level = medium;
            RealGame* realgameScene = new RealGame(level, player);
            view->setScene(realgameScene);
            QPushButton* backButton = realgameScene->backButton;
            QObject::connect(backButton, &QPushButton::clicked, [=]() {
                view->setScene(playerScene);
            });

        });
        QObject::connect(hardGameButton, &QPushButton::clicked, [=]() {
            difficulty level = hard;
            RealGame* realgameScene = new RealGame(level, player);
            view->setScene(realgameScene);
            QPushButton* backButton = realgameScene->backButton;
            QObject::connect(backButton, &QPushButton::clicked, [=]() {
                view->setScene(playerScene);
            });
        });
        QObject::connect(guestMainButton, &QPushButton::clicked, [=]() {
            view->setScene(firstScreen);
        });
    });



    QObject::connect(loginButton, &QPushButton::clicked, [=]() {
        QString userName = signinScene->userNameLE->text();
        QString password = signinScene->PasswordLE->text();
        player = new user(userName);
        playerScene = new PlayerScene(player);
        if(player->login(userName,password)){
            view->setScene(playerScene);
            QPushButton* easyGameButton = playerScene->Easy;
            QPushButton* mediumGameButton = playerScene->Medium;
            QPushButton* hardGameButton = playerScene->Hard;
            QPushButton* guestMainButton = playerScene->mainMenu;
            // Connect the button to a slot that switches the scene
            QObject::connect(easyGameButton, &QPushButton::clicked, [=]() {
                difficulty level = easy;
                 RealGame* realgameScene = new RealGame(level, player);
                view->setScene(realgameScene);
                 QPushButton* backButton = realgameScene->backButton;
                 QObject::connect(backButton, &QPushButton::clicked, [=]() {
                     view->setScene(playerScene);
                 });

            });
            QObject::connect(mediumGameButton, &QPushButton::clicked, [=]() {
                difficulty level = medium;
                RealGame* realgameScene = new RealGame(level, player);
                view->setScene(realgameScene);
                QPushButton* backButton = realgameScene->backButton;
                QObject::connect(backButton, &QPushButton::clicked, [=]() {
                    view->setScene(playerScene);
                });

            });
            QObject::connect(hardGameButton, &QPushButton::clicked, [=]() {
                difficulty level = hard;
                RealGame* realgameScene = new RealGame(level, player);
                view->setScene(realgameScene);
                QPushButton* backButton = realgameScene->backButton;
                QObject::connect(backButton, &QPushButton::clicked, [=]() {
                    view->setScene(playerScene);
                });
            });
            QObject::connect(guestMainButton, &QPushButton::clicked, [=]() {
                view->setScene(firstScreen);
            });

        }
        else{
            view->setScene(signinScene);
        }

    });

     QPushButton* exitButton = firstScreen->Exit;
    QObject::connect(exitButton, &QPushButton::clicked, &app, &QCoreApplication::quit);


    // Set the fixed size of the view
    view->setFixedSize(screenHeight, screenWidth);
    // Prevent scroll bars from appearing
    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    // Show the view
    view->show();
    return app.exec();
}
