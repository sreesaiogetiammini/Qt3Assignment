#include "signinscene.h"

SignInScene::SignInScene()
{
  this->constantElementDisplay();
    userNameL = new QLabel("UserName*:");
    PasswordL = new QLabel("Password*: ");
    userNameLE = new QLineEdit;
    PasswordLE = new QLineEdit;
    PasswordLE->setEchoMode(QLineEdit::Password);

    // Set up validators for the mandatory QLineEdit widgets
    QValidator* nonEmptyValidator = new QRegularExpressionValidator(QRegularExpression(".+"), this);
    userNameLE->setValidator(nonEmptyValidator);
    PasswordLE->setValidator(nonEmptyValidator);


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
    mainpage = new QPushButton("Main Menu");
    login->setEnabled(false);
    setFirstScreenQPushButtonProperties(reset);
    setFirstScreenQPushButtonProperties(mainpage);
    setFirstScreenQPushButtonProperties(login);

    connect(login, &QPushButton::clicked, this, &SignInScene::loginButtonClicked);
    connect(reset, &QPushButton::clicked, this, &SignInScene::resetButtonClicked);



}

void SignInScene::loginButtonClicked(){
    QString userName = userNameLE->text();
    QString password = PasswordLE->text();
    if (password.isEmpty()) {
        errorLabel->setText("Please enter password , it is blank");
        errorLabel->setVisible(true); // show the error label
        return;
    }
    errorLabel->setText("Login Successful");
    errorLabel->setStyleSheet("color: green");
    errorLabel->setVisible(true); // show the error label
    return;
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
