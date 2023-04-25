#pragma once
#include "playerscene.h"



PlayerScene::PlayerScene(user* player)
{
    this->constantElementDisplay();
    bool birthday = player->isBirthday();
    // Set up the labels
    QString userName =  player->username;
    if(userName.isEmpty()){
       welcomePlayerL = new QLabel("Welcome Guest");
    }
    else{
        welcomePlayerL = new QLabel("Welcome "+userName);
    }

    profilePicLabel = new QLabel();
    profilePicLabel->setFixedSize(100, 100);
    profilePicLabel->setStyleSheet("border-radius: 50px; border: 2px solid gray;");
    profilePicLabel->setAlignment(Qt::AlignCenter);

    QString filename = player->username+".png";
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

    QVector<user::scoreStruct> scores = player->scores ;
    int scoresSize = scores.size();
    QTableWidget *table = new QTableWidget(scoresSize, 3);
    table->setWindowTitle("Player Scores");
//    QSize size;

//    int numRows = 3;
//    int numCols = scoresSize;
//    int width = table->width();
//    int height = table->height();

//    // Calculate the size of each cell based on the table's size and number of rows and columns
//    int cellWidth = width / numCols;
//    int cellHeight = height / numRows;
//    size.setWidth(cellWidth);
//    size.setHeight(cellHeight);
//    table->setColumnWidth(cellWidth,cellHeight);

    // Set headers for each column
    QStringList headers;
    headers << "Match Date" << "Match Mode" << "Player Scores";
    table->setHorizontalHeaderLabels(headers);

    // Fill in the cells with data
    QTableWidgetItem *item;
    for (int row = 0; row < scoresSize; row++) {
        for (int col = 0; col < 3; col++) {
            if(col == 0){
                item = new QTableWidgetItem(QString(scores.at(row).date.toString()));
            }
            if(col == 1){
                item = new QTableWidgetItem(QString(scores.at(row).level));
            }

            if(col == 2){
                item = new QTableWidgetItem( QString::number(scores.at(row).score));
            }
            table->setItem(row, col, item);           // Set border for each cell
            table->item(row, col)->setBackground(QColor(Qt::white));
            table->item(row, col)->setTextAlignment(Qt::AlignCenter);
            table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            table->item(row, col)->setForeground(QBrush(QColor(Qt::red)));
            table->setStyleSheet("QTableWidget::item{border:1px solid #d4d4d4;}");

        }
    }

    // Set up the layout
    playerWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(welcomePlayerL, 0, 1);
    gridLayout->addWidget(profilePicLabel, 1, 1);
    gridLayout->addWidget(playerPageButtonBox, 3, 0, 1, 3);
    if(scores.size()!= 0 && !userName.isEmpty()){
         gridLayout->addWidget(table, 4, 0, 1, 3);
    }
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
