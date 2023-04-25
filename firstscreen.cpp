#pragma once
#include "headers.h"
#include "firstscreen.h"


FirstScreen::FirstScreen()
{
    this->constantElementDisplay();

    // Set up the dialog buttons
    buttonBox = new QDialogButtonBox(Qt:: Vertical);
    SignUp = new QPushButton("Sign Up");
    SignIn = new QPushButton("Sign In");
    GuestPlay = new QPushButton("Guest Play");
    Exit = new QPushButton("Exit");
    setFirstScreenQPushButtonProperties(SignUp);
    setFirstScreenQPushButtonProperties(SignIn);
    setFirstScreenQPushButtonProperties(GuestPlay);
    setFirstScreenQPushButtonProperties(Exit);

    buttonBox->addButton(SignUp, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(SignIn, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(GuestPlay, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(Exit, QDialogButtonBox::AcceptRole);


    // Set up the layout
    QWidget *buttonWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(buttonBox, 2, 0, 1, 2);
    gridLayout->addItem(new QSpacerItem(5, 10), 0, 2, 1, 1);// Add space
    QVBoxLayout *verticalLayout = new QVBoxLayout(buttonWidget);
    verticalLayout->addLayout(gridLayout);

    // Create a QGraphicsProxyWidget from the QWidget
    buttonProxyWidget = this->addWidget(buttonWidget);

    // Set the position of the QVBoxLayout
    QPointF newPos((sceneRect().width()/2 - buttonWidget->width())+ 100 , sceneRect().height()/4);
    buttonProxyWidget->setPos(newPos);






}



void FirstScreen::setFirstScreenQPushButtonProperties(QPushButton* button){
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    button->setFixedWidth(250);
    button->setMinimumHeight(100);
}


void FirstScreen::constantElementDisplay(){
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

