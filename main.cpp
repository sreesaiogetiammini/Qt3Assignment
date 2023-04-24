#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QObject>
#include "firstscreen.h"
#include "signupscene.h"
#include "signinscene.h"
#include "playerscene.h"
#include "realgame.h"

int main(int argc , char** argv){

    qreal screenHeight = 1400;
    qreal screenWidth = 900;
    QApplication app(argc,argv);

    FirstScreen* firstScreen = new FirstScreen();
    SignUpScene* signupScene = new SignUpScene();
    SignInScene* signinScene = new SignInScene();
    PlayerScene* playerScene = new PlayerScene();
    RealGame* realgameScene = new RealGame();


    QGraphicsView* view = new QGraphicsView();
    view->setScene(firstScreen);


    // Create a button to switch to scene2
    QPushButton* signUpSwitchButton = firstScreen->SignUp;
    QPushButton* signInSwitchButton = firstScreen->SignIn;
    QPushButton* guestSwitchButton = firstScreen->GuestPlay;

    QPushButton* signUpMainButton = signupScene->mainMenu;
    QPushButton* signInMainButton = signinScene->mainmenu;
    QPushButton* guestMainButton = playerScene->mainMenu;


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
         view->setScene(realgameScene);
     });
     QObject::connect(mediumGameButton, &QPushButton::clicked, [=]() {
         view->setScene(realgameScene);
     });
     QObject::connect(hardGameButton, &QPushButton::clicked, [=]() {
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
