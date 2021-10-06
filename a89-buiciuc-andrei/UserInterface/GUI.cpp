#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include "GUI.h"
#include "adminGUI.h"
#include "userGUI.h"


GUI::GUI(const ControllerAdmin &controllerAdmin, const ControllerUser &controllerUser, const Validator &validator) {
    this->controllerAdmin = controllerAdmin;
    this->controllerUser = controllerUser;
    this->validator = validator;
    this->isChecked = false;
    this->initGUI();
    this->connectSignals();
}

void GUI::initGUI() {
    // Set the background and fixed dimensions for the main window
    int x = (int)(this->width() * 1.25);
    int y = (int)(this->height() * 1.25);
    this->resize(x, y);

    QPixmap background(R"(D:\OOP Assignements\Assignmnents\a89-911-buiciuc-andrei\background.jpg)");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->mainPalette = palette;
    this->setPalette(palette);

    auto* mainLayout = new QVBoxLayout{this};

    // Text Label
    auto *textLabel = new QLabel{this};
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setText("Hello and welcome to C++ Tutorial Manager.\n"
                       "Choose an option below.");
    QFont font = textLabel->font();
    font.setPointSize(10);
    textLabel->setFont(font);
    mainLayout->addWidget(textLabel);

    // Output mode buttons
    auto *radioBox = new QGroupBox{"Output mode", this};
    auto *radioLayout = new QVBoxLayout{};
    this->radioCSV = new QRadioButton{"CSV File", this};
    this->radioCSV->toggled(true);
    this->radioHTML = new QRadioButton{"HTML File", this};
    radioLayout->addWidget(this->radioCSV);
    radioLayout->addWidget(this->radioHTML);
    radioBox->setLayout(radioLayout);
    mainLayout->addWidget(radioBox);

    // Administrator / User buttons
    this->administratorModeButton = new QPushButton{"Administrator mode", this};
    this->userModeButton = new QPushButton{"User mode", this};
    const QSize btnSize = QSize(350,400);
    this->administratorModeButton->setFixedSize(btnSize);
    this->userModeButton->setFixedSize(btnSize);

    auto* layoutButtons = new QHBoxLayout{};
    layoutButtons->addWidget(this->administratorModeButton);
    layoutButtons->addWidget(this->userModeButton);
    mainLayout->addLayout(layoutButtons);
}

void GUI::connectSignals() {
    QObject::connect(this->administratorModeButton, &QPushButton::clicked, this, &GUI::openAdministratorMode);
    QObject::connect(this->userModeButton, &QPushButton::clicked, this, &GUI::openUserMode);

    // Slots for the Output Mode
    QObject::connect(this->radioCSV, &QRadioButton::toggled, [this]() {
        if(this->isChecked) {
            // We have already toggled.
            delete this->absWatchlist;
        }
        this->absWatchlist = new CSVWatchlist(R"(D:\OOP Assignements\Assignmnents\a89-911-buiciuc-andrei\CSVWatchlist.txt)");
        this->isChecked = true;
    });

    QObject::connect(this->radioHTML, &QRadioButton::toggled, [this]() {
        if(this->isChecked) {
            // We have already toggled.
            delete this->absWatchlist;
        }
        this->absWatchlist = new HTMLWatchlist(R"(D:\OOP Assignements\Assignmnents\a89-911-buiciuc-andrei\HTMLWatchlist.html)");
        this->isChecked = true;
    });
}

void GUI::openAdministratorMode() {
    if(!this->isChecked) {
        return;
    }
    auto* adminWindow = new adminGUI{this->controllerAdmin, this->validator, this->mainPalette};
    adminWindow->show();
//    this->close();
}

void GUI::openUserMode() {
    if(!this->isChecked) {
        return;
    }
    auto* userWindow = new userGUI{this->controllerUser, this->controllerAdmin, this->validator, this->mainPalette,
                                   this->absWatchlist};
    userWindow->show();
//    this->close();
}

GUI::~GUI() {
    if(this->isChecked) {
        delete this->absWatchlist;
    }
}
