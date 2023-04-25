#pragma once
#include "headers.h"
#include "signupscene.h"




SignUpScene::SignUpScene()
{
    this->constantElementDisplay();
    // Set up the labels
    firstNameL = new QLabel("First Name*:");
    lastNameL = new QLabel("Last Name*:");
    dobL = new QLabel("DOB*:");
    genderL = new QLabel("Gender:");
    userNameL = new QLabel("UserName*:");
    setPasswordL = new QLabel("Password*: ");
    confirmPasswordL = new QLabel("Re-Type Password*");

    firstNameLE = new QLineEdit;
    firstNameLE->setMouseTracking(false);
    lastNameLE = new QLineEdit;
    lastNameLE->setFocusPolicy(Qt::ClickFocus);

    doBcalendar = new QCalendarWidget();
    doBcalendar->setMinimumDate(QDate(1900, 1, 1));
    doBcalendar->setMaximumDate(QDate::currentDate());
    doBcalendar->setSelectedDate(QDate());

    // Set up the gender radio buttons
    genderGB = new QGroupBox("");
    genderLayout = new QVBoxLayout;
    maleRB = new QRadioButton("Male");
    femaleRB = new QRadioButton("Female");
    genderLayout->addWidget(maleRB);
    genderLayout->addWidget(femaleRB);
    genderGB->setLayout(genderLayout);

    userNameLE = new QLineEdit;
    userNameLE->setFocusPolicy(Qt::ClickFocus);
    setPasswordLE = new QLineEdit;
    setPasswordLE->setFocusPolicy(Qt::ClickFocus);
    confirmPasswordLE = new QLineEdit;
    confirmPasswordLE->setFocusPolicy(Qt::ClickFocus);
    setPasswordLE->setEchoMode(QLineEdit::Password);
    confirmPasswordLE->setEchoMode(QLineEdit::Password);


    // Set the validator for the QLineEdit
    passwordLabel = new QLabel("Password should contain at least 8 characters  one number, upper and lower case letters.");
    passwordLabel->setStyleSheet("QLabel { color : blue; }");


    // Create a slot that checks if all mandatory fields are filled and enable/disable the push button accordingly
    auto checkMandatoryFields = [&]() {
        bool allFilled = this->FirstNameLastNameValidatons() &&
                         this->DateOfBirthValidations() &&
                         this->userNameValidations() &&
                         this->passwordValidation();
        submit->setEnabled(allFilled);
    };


    // Connect the textChanged() signals of the mandatory QLineEdit widgets to the checkMandatoryFields() slot
    connect(firstNameLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(lastNameLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(doBcalendar, &QCalendarWidget::selectionChanged, this, checkMandatoryFields);
    connect(userNameLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(setPasswordLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(confirmPasswordLE, &QLineEdit::textChanged, this, checkMandatoryFields);


    signUpPageButtonBox = new QDialogButtonBox(Qt:: Horizontal);
    reset = new QPushButton("Reset");
    submit = new QPushButton("Submit");
    mainMenu = new QPushButton("Main Menu");
    submit->setEnabled(false);
    setFirstScreenQPushButtonProperties(reset);
    setFirstScreenQPushButtonProperties(submit);
    setFirstScreenQPushButtonProperties(mainMenu);


    signUpPageButtonBox->addButton(reset, QDialogButtonBox::ResetRole);
    signUpPageButtonBox->addButton(submit, QDialogButtonBox::AcceptRole);
    signUpPageButtonBox->addButton(mainMenu, QDialogButtonBox::AcceptRole);
    connect(submit, &QPushButton::clicked, this, &SignUpScene::submitButtonClicked);
    connect(reset, &QPushButton::clicked, this, &SignUpScene::resetButtonClicked);
    connect(mainMenu, &QPushButton::clicked, this, &SignUpScene::mainMenuButtonClicked);



    profilePicLabel = new QLabel("Profile Pic");
    profilePicLabel->setFixedSize(100, 100);
    profilePicLabel->setStyleSheet("border-radius: 50px; border: 2px solid gray;");
    profilePicLabel->setAlignment(Qt::AlignCenter);

    choosePicButton = new QPushButton("Upload Picture");
    choosePicButton->setFixedWidth(100);
    connect(choosePicButton, &QPushButton::clicked, this, &SignUpScene::chooseProfilePic);

    // Create a QLabel widget to display error messages
    errorLabel = new QLabel("");
    errorLabel->setVisible(false); // hide the label initially

    // Set up the layout
    signUpWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(profilePicLabel, 0, 0, 1, 2, Qt::AlignCenter);
    gridLayout->addWidget(choosePicButton, 1, 0, 1, 2, Qt::AlignCenter);
    gridLayout->addWidget(firstNameL, 2, 0);
    gridLayout->addWidget(firstNameLE, 2, 1);
    gridLayout->addWidget(lastNameL, 3, 0);
    gridLayout->addWidget(lastNameLE, 3, 1);
    gridLayout->addWidget(dobL, 4, 0);
    gridLayout->addWidget(doBcalendar, 4, 1);
    gridLayout->addWidget(genderL, 5, 0);
    gridLayout->addWidget(genderGB, 5, 1);
    gridLayout->addWidget(userNameL, 6, 0);
    gridLayout->addWidget(userNameLE, 6, 1);
    gridLayout->addWidget(passwordLabel, 7, 1);
    gridLayout->addWidget(setPasswordL, 8, 0);
    gridLayout->addWidget(setPasswordLE, 8, 1);
    gridLayout->addWidget(confirmPasswordL, 9, 0);
    gridLayout->addWidget(confirmPasswordLE, 9, 1);
    gridLayout->addWidget(errorLabel, 10, 1, 1, 2);
    gridLayout->addWidget(signUpPageButtonBox, 11, 0, 1, 3);

    gridLayout->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);
    QVBoxLayout *verticalLayout = new QVBoxLayout(signUpWidget);
    verticalLayout->addLayout(gridLayout);

    // Create a QGraphicsProxyWidget from the QWidget
    signUpProxyWidget = this->addWidget(signUpWidget);

    // Set the position of the QVBoxLayout
    QPointF newPos((sceneRect().width()/2 - signUpWidget->width())+ 300 , sceneRect().height()/8);
    signUpProxyWidget->setPos(newPos);

}


void SignUpScene::chooseProfilePic() {

    filename = QFileDialog::getOpenFileName(this->choosePicButton, "Choose Picture", "", "Images (*.png *.jpg *.bmp)");

    QImage image;

    if (image.load(filename)) {
        profilePic = QPixmap(filename);
        profilePic = profilePic.scaled(profilePicLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        profilePicLabel->setPixmap(profilePic);
    }

    else {
        qDebug() << "Failed to load image.";
    }

//    if (filename != "") {
//        QPixmap profilePic(filename);
//        profilePic = profilePic.scaled(profilePicLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
//        profilePicLabel->setPixmap(profilePic);
//    }
}

void SignUpScene::setFirstScreenQPushButtonProperties(QPushButton* button){
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    button->setFixedWidth(75);
    button->setMinimumHeight(50);
}

void SignUpScene::submitButtonClicked(){
    QString firstName = firstNameLE->text();
    QString lastName = lastNameLE->text();
    QString doB = doBcalendar->selectedDate().toString("dd-MM-yyyy");
    QString userName = userNameLE->text().toLower();
    QString password = setPasswordLE->text();
    QString confirmPassword = confirmPasswordLE->text();
    user *newUser = new user(userName);
    newUser->signup(userName, password, firstName, lastName, doB, filename);
    errorLabel->setText("Signed Up Suceessfully");
    errorLabel->setStyleSheet("color: green");
    errorLabel->setVisible(true); //

    QPixmap pixmap = profilePic;
    QString newFileName = userNameLE->text().toLower()+".png";// Replace with your own QPixmap object
    QString filename = "/Users/srees/Desktop/CS6015/Qt3Assignment/"+newFileName; // Replace with your desired filename in the resources folder

    // Create a QFile object to write to the file
    QFile file(filename);

    // Open the file for writing
    if (file.open(QIODevice::WriteOnly)) {
        // Save the QPixmap object to the file
        pixmap.save(&file, "PNG");

        // Close the file
        file.close();
    } else {
        qDebug() << filename;
        qDebug() << "Failed to save image.";
    }
    submit->setEnabled(false);
    return;

}




void SignUpScene::resetButtonClicked(){
    firstNameLE->clear();
    lastNameLE->clear();
    userNameLE->clear();
    doBcalendar->clearFocus();
    setPasswordLE->clear();
    confirmPasswordLE->clear();
    return;
}

void SignUpScene::mainMenuButtonClicked(){
     this->resetButtonClicked();
}



bool SignUpScene::FirstNameLastNameValidatons(){
    QString firstName = firstNameLE->text();
    QString lastName = lastNameLE->text();
    if (firstName.isEmpty() || lastName.isEmpty()) {
        errorLabel->setText("Please enter first and last name");
        errorLabel->setStyleSheet("color: red");
        errorLabel->setVisible(true); // show the error label
        return false;
    }

    else {
        QRegularExpression regex("^[a-zA-Z]+([ '-][a-zA-Z]+)*$");
        bool validCheck = regex.match(firstName).hasMatch() && regex.match(lastName).hasMatch() ;
        if(!validCheck){
            errorLabel->setText("First Name or Last Name are not Valid");
            errorLabel->setStyleSheet("color: red");
            errorLabel->setVisible(true); // show the error label
            return false;
        }
        errorLabel->setVisible(false);
        return true;
    }
}

bool SignUpScene::DateOfBirthValidations(){
    QDate selectedDate = doBcalendar->selectedDate();
    if (selectedDate.isNull() || selectedDate == QDate::currentDate() || selectedDate > QDate::currentDate().addYears(-5) ) {
        errorLabel->setText("Please select a valid date of birth (you must be at least 5 years old)");
        errorLabel->setStyleSheet("color: red");
        errorLabel->setVisible(true); // show the error label
        doBcalendar->setSelectedDate(QDate());
        return false;
    }
    else {
        errorLabel->setVisible(false);
        return true;
    }
}

bool SignUpScene::passwordValidation(){
    QString password1 = setPasswordLE->text();
    QString password2 = confirmPasswordLE->text();
    // Check for password match
    if (password1 != password2) {
        errorLabel->setText("Passwords do not match.");
        errorLabel->setStyleSheet("color: red");
        errorLabel->setVisible(true); // show the error label
        return false;
    }
    // Check for password strength
    else {
        QRegularExpression regex("(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,}");
        if (regex.match(password1).hasMatch()) {
            errorLabel->setVisible(false);
            passwordLabel->setVisible(false);
            return true;
        }
        else {
            passwordLabel->setStyleSheet("color: red");
            errorLabel->setVisible(false); // show the error label
            return false;
        }
    }
}

bool SignUpScene::userNameValidations(){
    QString userNameText = userNameLE->text().toLower();
    if (userNameText.isEmpty()) {
        errorLabel->setText("Please enter UserName");
        errorLabel->setStyleSheet("color: red");
        errorLabel->setVisible(true);
        return false;
    }

    else {
        QRegularExpression regex("^[a-zA-Z0-9_]{4,20}$");
        bool validCheck = regex.match(userNameText).hasMatch() ;
        if(!validCheck){
            errorLabel->setText("Please enter Valid UserName");
            errorLabel->setStyleSheet("color: red");
            errorLabel->setVisible(true);
            return false;
        }
        else {
            userNameLE->setText(userNameText);
            user* loginUser = new user(userNameText);
            QJsonArray jsonArray = loginUser->usersArray;
            for (const QJsonValue &value : jsonArray) {
                QJsonObject obj = value.toObject();
                QString existingUsername = obj.value("username").toString();
                if (existingUsername == userNameText) {
                    errorLabel->setText("UserName :"+userNameText+" already used please use other ");
                    errorLabel->setStyleSheet("color: red");
                    errorLabel->setVisible(true);
                    return false;
                }
            }

        }
    }
    errorLabel->setVisible(false);
    return true;
}



void SignUpScene::constantElementDisplay(){
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

