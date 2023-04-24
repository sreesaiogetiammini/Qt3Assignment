#include "realgame.h"

RealGame::RealGame()
{
    this->constantElementDisplay();

    // Add water droplets
    srand(time(NULL));
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, [=]() {
        Clouds *cloud1 = new Clouds();
        addItem(cloud1);
        cloud1->setPos(0,0);
        cloud1->move();
        water *drop = new water();
        drop->setPos(rand()%700, 0);
        addItem(drop);
    });
    timer->start(2000);
}


void RealGame::keyPressEvent(QKeyEvent* event)
{
    qreal moveBy = 30;
    switch (event->key()) {
    case Qt::Key_Left:
        if (bucketImg->pos().x() > 0) {
            bucketImg->setPos(bucketImg->pos() - QPointF(moveBy, 0));
        }
        break;
    case Qt::Key_Right:
        if (bucketImg->pos().x() + bucketImg->boundingRect().width() < sceneRect().width()) {
            bucketImg->setPos(bucketImg->pos() + QPointF(moveBy, 0));
        }
        break;
    case Qt::Key_Up:
        if (bucketImg->pos().y() > 100) {
            bucketImg->setPos(bucketImg->pos() - QPointF(0, moveBy));
        }
        break;
    case Qt::Key_Down:
        if (bucketImg->pos().y() + bucketImg->boundingRect().height() < sceneRect().height()) {
            bucketImg->setPos(bucketImg->pos() + QPointF(0, moveBy));
        }
        break;
    default:
        break;
    }


    QList<QGraphicsItem*> collisions = bucketImg->collidingItems();
    for (QGraphicsItem* item : collisions) {
        if (item->type() == water::Type) {
            // Remove droplet from scene and delete it
            this->removeItem(item);
            delete item;
        }
        else if (item->type() == Clouds::Type) {
            // Remove droplet from scene and delete it
            this->addItem(item);
        }
    }
}

void RealGame::constantElementDisplay(){

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
}
