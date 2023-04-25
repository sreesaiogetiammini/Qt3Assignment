#pragma once
#include "headers.h"
#include "signinscene.h"


SignInScene::SignInScene()
{
  this->constantElementDisplay();
    userNameL = new QLabel("UserName*:");
    PasswordL = new QLabel("Password*: ");
    userNameLE = new QLineEdit;
    PasswordLE = new QLineEdit;
    PasswordLE->setEchoMode(QLineEdit::Password);

    // Create a slot that checks if all mandatory fields are filled and enable/disable the push button accordingly
    auto checkMandatoryFields = [&]() {
        bool allFilled = userNameLE->hasAcceptableInput() && PasswordLE->hasAcceptableInput() ;
        login->setEnabled(allFilled);
    };

    // Connect the textChanged() signals of the mandatory QLineEdit widgets to the checkMandatoryFields() slot
    connect(userNameLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(PasswordLE, &QLineEdit::textChanged, this, checkMandatoryFields);

    signInPageButtonBox = new QDialogButtonBox(Qt:: Horizontal);
    reset = new QPushButton("Reset");
    login = new QPushButton("Login");
    mainmenu = new QPushButton("Main Menu");
    setFirstScreenQPushButtonProperties(reset);
    setFirstScreenQPushButtonProperties(mainmenu);
    setFirstScreenQPushButtonProperties(login);
    signInPageButtonBox->addButton(reset, QDialogButtonBox::ResetRole);
    signInPageButtonBox->addButton(login, QDialogButtonBox::AcceptRole);
    signInPageButtonBox->addButton(mainmenu, QDialogButtonBox::AcceptRole);
    connect(login, &QPushButton::clicked, this, &SignInScene::loginButtonClicked);
    connect(reset, &QPushButton::clicked, this, &SignInScene::resetButtonClicked);

    // Create a QLabel widget to display error messages
    errorLabel = new QLabel("Error message");
    errorLabel->setStyleSheet("color: red");
    errorLabel->setVisible(false); // hide the label initially

    // Set up the layout
    signInWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(userNameL, 1, 0);
    gridLayout->addWidget(userNameLE, 1, 1);
    gridLayout->addWidget(PasswordL, 2, 0);
    gridLayout->addWidget(PasswordLE, 2, 1);
    gridLayout->addWidget(signInPageButtonBox, 4, 0, 1, 3);
    gridLayout->addWidget(errorLabel, 3, 1, 1, 2);
    gridLayout->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);
    QVBoxLayout *verticalLayout = new QVBoxLayout(signInWidget);
    verticalLayout->addLayout(gridLayout);

    // Create a QGraphicsProxyWidget from the QWidget
    signInProxyWidget = this->addWidget(signInWidget);

    // Set the position of the QVBoxLayout
    QPointF newPos((sceneRect().width()/2 - signInWidget->width())+100 , sceneRect().height()/8);
    signInProxyWidget->setPos(newPos);

}

void SignInScene::loginButtonClicked(){
    QString userName = userNameLE->text();
    QString password = PasswordLE->text();
    if (password.isEmpty() || userName.isEmpty()) {
        errorLabel->setText("Please enter username or password , it is blank");
        errorLabel->setVisible(true); // show the error label
        return;
    }
    user* loginUser = new user(userName);
    if(loginUser->login(userName,password))
    {
        errorLabel->setText("Login Successful");
        errorLabel->setStyleSheet("color: green");
        errorLabel->setVisible(true); // show the error label
        return;
    }

    else {
        errorLabel->setText("Login Failed");
        errorLabel->setStyleSheet("color: red");
        errorLabel->setVisible(true); // show the error label
        this->resetButtonClicked();
        return;
    }
}

void SignInScene::resetButtonClicked(){
    userNameLE->clear();
    PasswordLE->clear();
    return;
}



void SignInScene::setFirstScreenQPushButtonProperties(QPushButton* button){
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    button->setFixedWidth(75);
    button->setMinimumHeight(50);
}


void SignInScene::constantElementDisplay(){
    // Create the text item and set its properties
    QGraphicsTextItem* gameName = new QGraphicsTextItem("Catch A Drop");
    QFont font("Arial", 56, QFont::Bold);
    font.setItalic(true);
    gameName->setFont(font);

    // Add effects to the text item
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(8);
    shadowEffect->setColor(QColor(0, 0, 0, 127));
    shadowEffect->setOffset(4, 4);
    gameName->setGraphicsEffect(shadowEffect);

    QGraphicsColorizeEffect* colorizeEffect = new QGraphicsColorizeEffect();
    colorizeEffect->setColor(QColor(255, 255, 0, 127));
    gameName->setGraphicsEffect(colorizeEffect);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.5);
    gameName->setGraphicsEffect(opacityEffect);
    gameName->setDefaultTextColor(Qt::black);
    // Calculate the center point of the screen
    gameName->setPos(500,0);
    this->addItem(gameName);
    qreal screenHeight = 900;
    qreal screenWidth = 1400;
    setBackgroundBrush(QBrush(QImage(":/background.jpg").scaledToHeight(screenHeight).scaledToWidth(screenWidth)));
    setSceneRect(0, 0, screenWidth-2, screenHeight-2);

    // Create the bucket object and set its pixmap
    bucketImg = new bucket();
    // Set the bucket object as focusable
    bucketImg->setFlag(QGraphicsItem::ItemIsFocusable);
    addItem(bucketImg);
    // Set the bucket object as the focus item
    bucketImg->setFocus();


    MusicOn = new QPushButton();
    QIcon icon(":/musicon.png"); // create QIcon object with image path
    MusicOn->setIcon(icon); // set the icon to the button
    MusicOn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    MusicOn->setFixedWidth(100);
    MusicOn->setMinimumHeight(30);

    MusicOff = new QPushButton();
    QIcon icon2(":/musicoff.png"); // create QIcon object with image path
    MusicOff->setIcon(icon2); // set the icon to the button
    MusicOff->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    MusicOff->setFixedWidth(100);
    MusicOff->setMinimumHeight(30);
    MusicOff->setEnabled(false);


    // Set up the layout
    QDialogButtonBox*  musicbuttonBox = new QDialogButtonBox(Qt:: Horizontal);
    musicbuttonBox->addButton(MusicOn, QDialogButtonBox::AcceptRole);
    musicbuttonBox->addButton(MusicOff, QDialogButtonBox::AcceptRole);


    auto musicOnClick =  [&]() {
        audioOutput->setVolume(80);
        player->play();
        MusicOn->setEnabled(false);
        MusicOff->setEnabled(true);
    };

    auto musicOffClick =  [&]() {
        player->pause();
        MusicOff->setEnabled(false);
        MusicOn->setEnabled(true);
    };

    // Create a QMediaPlayer instance
    player = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setSource(QUrl::fromLocalFile(":/music.mp3"));
    connect(MusicOn, &QPushButton::clicked, this, musicOnClick);
    connect(MusicOff, &QPushButton::clicked, this, musicOffClick);

    // Set up the layout
    QWidget *musicWidget = new QWidget();
    QGridLayout *gridLayout3 = new QGridLayout();
    gridLayout3->addWidget(musicbuttonBox);
    gridLayout3->addItem(new QSpacerItem(5, 10), 0, 2, 1, 1); // Add space
    QVBoxLayout *verticalLayout3 = new QVBoxLayout(musicWidget);
    verticalLayout3->addLayout(gridLayout3);

    // Create a QGraphicsProxyWidget from the QWidget
    musicButtonsProxyWidget = this->addWidget(musicWidget);
    QPointF newPos2((sceneRect().width() - musicWidget->width()), 0);
    musicButtonsProxyWidget->setPos(newPos2);
}

