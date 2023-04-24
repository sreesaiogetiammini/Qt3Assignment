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
    // Set up the line edits and spin box
    firstNameLE = new QLineEdit;
    lastNameLE = new QLineEdit;
    doBcalendar = new QCalendarWidget();

    // Set the minimum and maximum selectable dates
    doBcalendar->setMinimumDate(QDate(1900, 1, 1));
    doBcalendar->setMaximumDate(QDate::currentDate().addYears(-5));
    doBcalendar->setFocusPolicy(Qt::NoFocus);

    // Set up the gender radio buttons
    genderGB = new QGroupBox("");
    genderLayout = new QVBoxLayout;
    maleRB = new QRadioButton("Male");
    femaleRB = new QRadioButton("Female");
    genderLayout->addWidget(maleRB);
    genderLayout->addWidget(femaleRB);
    genderGB->setLayout(genderLayout);

    userNameLE = new QLineEdit;
    setPasswordLE = new QLineEdit;
    confirmPasswordLE = new QLineEdit;
    setPasswordLE->setEchoMode(QLineEdit::Password);
    confirmPasswordLE->setEchoMode(QLineEdit::Password);


    // Set the validator for the QLineEdit
    QLabel *passwordLabel = new QLabel("Password should contain at least 8 characters  one number, upper and lower case letters.");
    passwordLabel->setStyleSheet("QLabel { color : blue; }");

    signUpPageButtonBox = new QDialogButtonBox(Qt:: Horizontal);
    reset = new QPushButton("Reset");
    submit = new QPushButton("Submit");
    mainMenu = new QPushButton("Main Menu");
    submit->setEnabled(false);
    setFirstScreenQPushButtonProperties(reset);
    setFirstScreenQPushButtonProperties(submit);
    setFirstScreenQPushButtonProperties(mainMenu);

    // Set up validators for the mandatory QLineEdit widgets
    QValidator* nonEmptyValidator = new QRegularExpressionValidator(QRegularExpression(".+"), this);
    firstNameLE->setValidator(nonEmptyValidator);
    lastNameLE->setValidator(nonEmptyValidator);
    userNameLE->setValidator(nonEmptyValidator);
    setPasswordLE->setValidator(new PasswordValidator());
    confirmPasswordLE->setValidator(new PasswordValidator());

    // Create a slot that checks if all mandatory fields are filled and enable/disable the push button accordingly
    auto checkMandatoryFields = [&]() {
        bool allFilled = firstNameLE->hasAcceptableInput() &&
                         lastNameLE->hasAcceptableInput() &&
                         userNameLE->hasAcceptableInput() &&
                         doBcalendar->selectedDate().isValid() &&
                         setPasswordLE->hasAcceptableInput() &&
                         confirmPasswordLE->hasAcceptableInput();
        submit->setEnabled(allFilled);
    };

    // Connect the textChanged() signals of the mandatory QLineEdit widgets to the checkMandatoryFields() slot
    connect(firstNameLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(lastNameLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(doBcalendar, &QCalendarWidget::selectionChanged, this, checkMandatoryFields);
    connect(userNameLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(setPasswordLE, &QLineEdit::textChanged, this, checkMandatoryFields);
    connect(confirmPasswordLE, &QLineEdit::textChanged, this, checkMandatoryFields);

    signUpPageButtonBox->addButton(reset, QDialogButtonBox::ResetRole);
    signUpPageButtonBox->addButton(submit, QDialogButtonBox::AcceptRole);
    signUpPageButtonBox->addButton(mainMenu, QDialogButtonBox::AcceptRole);
    connect(submit, &QPushButton::clicked, this, &SignUpScene::submitButtonClicked);
    connect(reset, &QPushButton::clicked, this, &SignUpScene::resetButtonClicked);

    profilePicLabel = new QLabel("Profile Pic");
    profilePicLabel->setFixedSize(100, 100);
    profilePicLabel->setStyleSheet("border-radius: 50px; border: 2px solid gray;");
    profilePicLabel->setAlignment(Qt::AlignCenter);

    choosePicButton = new QPushButton("Upload Picture");
    choosePicButton->setFixedWidth(100);
    connect(choosePicButton, &QPushButton::clicked, this, &SignUpScene::chooseProfilePic);

    // Create a QLabel widget to display error messages
    errorLabel = new QLabel("Error message");
    errorLabel->setStyleSheet("color: red");
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
    gridLayout->addWidget(signUpPageButtonBox, 10, 0, 1, 3);
    gridLayout->addWidget(errorLabel, 10, 1, 1, 2);
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
    QString filename = QFileDialog::getOpenFileName(this->choosePicButton, "Choose Picture", "", "Images (*.png *.jpg *.bmp)");
    if (filename != "") {
        QPixmap profilePic(filename);
        profilePic = profilePic.scaled(profilePicLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        profilePicLabel->setPixmap(profilePic);
    }
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
    QString userName = userNameLE->text();
    QString password = setPasswordLE->text();
    QString confirmPassword = confirmPasswordLE->text();
    bool allChecked = false;

    // Validate the input data and display an error message if needed
    if (firstName.isEmpty() || lastName.isEmpty()) {
        errorLabel->setText("Please enter first and last name");
        errorLabel->setVisible(true); // show the error label
        return;
    }

    if(!doBcalendar->selectedDate().isValid()) {
        errorLabel->setText("Please enter valid Date of Birth");
        errorLabel->setVisible(true); // show the error label
        return;
    }

    if(doB.isEmpty()){
        errorLabel->setText("Please enter Valid Date of Birth");
        errorLabel->setVisible(true); // show the error label
        return;
    }

    if (password.isEmpty() || confirmPassword.isEmpty()) {
        errorLabel->setText("Please enter password , it is blank");
        errorLabel->setVisible(true); // show the error label
        return;
    }

    errorLabel->setText("Signed Up Suceessfully");
    errorLabel->setStyleSheet("color: green");
    errorLabel->setVisible(true); //

    user *newUser = new user();

    newUser->signup(userName, password, firstName, lastName, doB);

    return;

}


void SignUpScene::resetButtonClicked(){

    firstNameLE->clear();
    lastNameLE->clear();
    userNameLE->clear();
    doBcalendar->clearFocus();
    setPasswordLE->clear();
    confirmPasswordLE->clear();
}

void SignUpScene::updateButtonState(QLineEdit* lineEdit) {
    // Check if the input fields are filled and enable or disable the button accordingly
    if (lineEdit->text().isEmpty()){
        submit->setEnabled(false);
    } else {
        submit->setEnabled(true);
    }
}


bool SignUpScene::isPasswordValid(const QString& password) {
    QRegularExpression re("(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).+");
    return re.match(password).hasMatch();
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


