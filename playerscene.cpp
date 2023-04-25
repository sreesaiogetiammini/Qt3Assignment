#pragma once
#include "headers.h"
#include "playerscene.h"



PlayerScene::PlayerScene()
{
    this->constantElementDisplay();
    bool birthday = true;
    // Set up the labels
    QString guest = "Guest";
    welcomePlayerL = new QLabel("Welcome "+guest);

    profilePicLabel = new QLabel();
    profilePicLabel->setFixedSize(100, 100);
    profilePicLabel->setStyleSheet("border-radius: 50px; border: 2px solid gray;");
    profilePicLabel->setAlignment(Qt::AlignCenter);

    QString filename = "";
    if (filename != "") {
        QPixmap profilePic(filename);
        profilePic = profilePic.scaled(profilePicLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        profilePicLabel->setPixmap(profilePic);
    }

    else{
        QPixmap profilePic(":/bucket.png");
        profilePic = profilePic.scaled(profilePicLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        profilePicLabel->setPixmap(profilePic);
    }

    playerPageButtonBox = new QDialogButtonBox(Qt:: Horizontal);
    Easy = new QPushButton("Easy");
    Medium = new QPushButton("Medium");
    Hard = new QPushButton("Hard");
    mainMenu = new QPushButton("Main Menu");
    setFirstScreenQPushButtonProperties(Easy);
    setFirstScreenQPushButtonProperties(Medium);
    setFirstScreenQPushButtonProperties(Hard);
    setFirstScreenQPushButtonProperties(mainMenu);
    playerPageButtonBox->addButton(mainMenu, QDialogButtonBox::AcceptRole);
    playerPageButtonBox->addButton(Hard, QDialogButtonBox::AcceptRole);
    playerPageButtonBox->addButton(Medium, QDialogButtonBox::AcceptRole);
    playerPageButtonBox->addButton(Easy, QDialogButtonBox::AcceptRole);

    int scoresSize = 10;
    QTableWidget *table = new QTableWidget(scoresSize, 3);
    table->setWindowTitle("Player Scores");


    // Set headers for each column
    QStringList headers;
    headers << "Match Date" << "Match Mode" << "Player Scores";
    table->setHorizontalHeaderLabels(headers);

    // Fill in the cells with data
    QTableWidgetItem *item;
    for (int row = 0; row < scoresSize; row++) {
        for (int col = 0; col < 3; col++) {
            item = new QTableWidgetItem(QString("Row %1, Col %2").arg(row+1).arg(col+1));
            table->setItem(row, col, item);

            // Set border for each cell
            table->item(row, col)->setBackground(QColor(Qt::white));
            table->item(row, col)->setTextAlignment(Qt::AlignCenter);
            table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            table->item(row, col)->setForeground(QBrush(QColor(Qt::white)));
            table->setStyleSheet("QTableWidget::item{border:1px solid #d4d4d4;}");

        }
    }

    // Set up the layout
    playerWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(welcomePlayerL, 0, 1);
    gridLayout->addWidget(profilePicLabel, 1, 1);
    gridLayout->addWidget(playerPageButtonBox, 3, 0, 1, 3);
    gridLayout->addWidget(table, 4, 0, 1, 3);
    gridLayout->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);
    QVBoxLayout *verticalLayout = new QVBoxLayout(playerWidget);
    verticalLayout->addLayout(gridLayout);

    // Create a QGraphicsProxyWidget from the QWidget
    playerProxyWidget = this->addWidget(playerWidget);

    // Set the position of the QVBoxLayout
    QPointF newPos((sceneRect().width()/2 - playerWidget->width())+200 , sceneRect().height()/8);
    playerProxyWidget->setPos(newPos);


    if(birthday){
        ImageWidget *imageWidget = new ImageWidget();
        // Create a QGraphicsProxyWidget and set its widget to the ImageWidget
        QGraphicsProxyWidget *birthdayProxyWidget = new QGraphicsProxyWidget();
        birthdayProxyWidget->setWidget(imageWidget);
        this->addItem(birthdayProxyWidget);
        QPointF newPos((sceneRect().width() - imageWidget->width())-200, sceneRect().height()/8);
        birthdayProxyWidget->setPos(newPos);
        connect(imageWidget, &ImageWidget::close, [imageWidget, this,birthdayProxyWidget]() {
            this->removeItem(birthdayProxyWidget);
            // Delete the ImageWidget instance
            delete imageWidget;
        });
    }


}

void PlayerScene::setFirstScreenQPushButtonProperties(QPushButton* button){
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    button->setFixedWidth(100);
    button->setMinimumHeight(50);
}


void PlayerScene::constantElementDisplay(){

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


    // Set up the layout

    QDialogButtonBox*  musicbuttonBox = new QDialogButtonBox(Qt:: Horizontal);
    musicbuttonBox->addButton(MusicOn, QDialogButtonBox::AcceptRole);
    musicbuttonBox->addButton(MusicOff, QDialogButtonBox::AcceptRole);

    // Set up the layout
    QWidget *musicWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(musicbuttonBox);
    gridLayout->addItem(new QSpacerItem(5, 10), 0, 2, 1, 1); // Add space
    QVBoxLayout *verticalLayout = new QVBoxLayout(musicWidget);
    verticalLayout->addLayout(gridLayout);

    // Create a QGraphicsProxyWidget from the QWidget
    musicButtonsProxyWidget = this->addWidget(musicWidget);
    QPointF newPos2((sceneRect().width() - musicWidget->width()), 0);
    musicButtonsProxyWidget->setPos(newPos2);

    // Create a QMediaPlayer instance
    QMediaPlayer* player = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("music.mp3"));



    // Create a slot that checks if all mandatory fields are filled and enable/disable the push button accordingly
    auto musicOn = [&]() {
        audioOutput->setVolume(50);
        player->play();
    };

    auto musicOff = [&]() {
        player->pause();
    };
    connect(MusicOn, &QPushButton::clicked, this, musicOn);
    connect(MusicOff, &QPushButton::clicked, this, musicOff);
}


void PlayerScene:: displayBirthDayGreeting()
{

    QWidget* birthdayWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(birthdayWidget);
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(":/birthday.png").scaledToWidth(700).scaledToHeight(500));
    layout->addWidget(imageLabel);
    closeBirthdayButton = new QPushButton("Close");
    layout->addWidget(closeBirthdayButton);
    // Create a QGraphicsProxyWidget from the QWidget
    birthdayProxyWidget = this->addWidget(birthdayWidget);
    // Set the position of the QVBoxLayout
    QPointF newPos((sceneRect().width() - birthdayWidget->width())-200, sceneRect().height()/8);
    birthdayProxyWidget->setPos(newPos);

}
