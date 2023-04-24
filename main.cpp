#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QObject>
#include "firstscreen.h"
#include "signupscene.h"
#include "signinscene.h"

int main(int argc , char** argv){

    qreal screenHeight = 1400;
    qreal screenWidth = 900;
    QApplication app(argc,argv);

    FirstScreen* firstScreen = new FirstScreen();
    SignUpScene* signupScene = new SignUpScene();
    SignInScene* signinScene = new SignInScene();




    QGraphicsView* view = new QGraphicsView();
    view->setScene(firstScreen);


    // Create a button to switch to scene2
    QPushButton* switchButton = firstScreen->SignUp;

    QPushButton* signUpMainButton = signupScene->login;
    QPushButton* signInMainButton = signinScene->mainpage;

    // Connect the button to a slot that switches the scene
    QObject::connect(switchButton, &QPushButton::clicked, [=]() {
      view->setScene(signupScene);

    });

     // Connect the button to a slot that switches the scene
     QObject::connect(signUpMainButton, &QPushButton::clicked, [=]() {

         view->setScene(firstScreen);

     });

    // Connect the button to a slot that switches the scene
    QObject::connect(signInMainButton, &QPushButton::clicked, [=]() {

        view->setScene(firstScreen);

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
