#include "adminGUI.h"
#include "../Exception/customException.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>
#include <QModelIndex>
#include <QMessageBox>
#include <QtCharts>
#include <QBarSet>

adminGUI::adminGUI(const ControllerAdmin &controllerAdmin, const Validator &validator, const QPalette& palette) {
    this->controllerAdmin = controllerAdmin;
    this->validator = validator;
    this->mainPalette = palette;
    this->initGUI(this->mainPalette);
    this->populateTutorialList();
    this->connectSignalsSlots();
}

void adminGUI::initGUI(const QPalette& palette) {
    // Set fixed dimensions for the Administrator Window.
    int x =(int)(this->width() * 1.25);
    int y = (int)(this->height() * 1.25);
    this->resize(x, y);

    // Set the main palette / background for the Administrator Window.
    this->setPalette(palette);

    // Create the graphical elements.
    this->tutorialListWidget = new QListWidget{this};
    this->titleLineEdit = new QLineEdit{this};
    this->presenterLineEdit = new QLineEdit{this};
    this->linkLineEdit = new QLineEdit{this};
    this->minutesLineEdit = new QLineEdit{this};
    this->secondsLineEdit = new QLineEdit{this};
    this->likesLineEdit = new QLineEdit{this};
    this->addButton = new QPushButton{"Add tutorial", this};
    this->deleteButton = new QPushButton{"Delete tutorial", this};
    this->updateButton = new QPushButton{"Update tutorial", this};
    this->seeChartButton = new QPushButton{"See chart", this};

    this->undoButton = new QPushButton{"Undo", this};
    this->redoButton = new QPushButton{"Redo", this};

    auto *adminLayout = new QVBoxLayout{this};
    adminLayout->addWidget(this->tutorialListWidget);

    auto *tutorialDataLayout = new QFormLayout{};
    tutorialDataLayout->addRow("Title", this->titleLineEdit);
    tutorialDataLayout->addRow("Presenter", this->presenterLineEdit);
    tutorialDataLayout->addRow("Link", this->linkLineEdit);
    tutorialDataLayout->addRow("Minutes", this->minutesLineEdit);
    tutorialDataLayout->addRow("Seconds", this->secondsLineEdit);
    tutorialDataLayout->addRow("Likes", this->likesLineEdit);
    adminLayout->addLayout(tutorialDataLayout);

    auto *buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->updateButton, 1, 0);
    buttonsLayout->addWidget(this->seeChartButton, 1, 1);

    buttonsLayout->addWidget(this->undoButton, 2, 0);
    buttonsLayout->addWidget(this->redoButton, 2, 1);

    adminLayout->addLayout(buttonsLayout);
}

void adminGUI::populateTutorialList() {
    this->tutorialListWidget->clear();

    std::vector<Tutorial> tutorials = this->controllerAdmin.getRepo().getData();
    for(const auto& tutorial: tutorials) {
        this->tutorialListWidget->addItem(QString::fromStdString(tutorial.getTitle() + " | " + tutorial.getPresenter()));
    }
}

void adminGUI::connectSignalsSlots() {
    // Slot for item selection.
    QObject::connect(this->tutorialListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getIndex();
        if(selectedIndex == -1) {
            return;
        }
        Tutorial tutorial = this->controllerAdmin.getRepo().getData()[selectedIndex];
        this->titleLineEdit->setText(QString::fromStdString(tutorial.getTitle()));
        this->presenterLineEdit->setText(QString::fromStdString(tutorial.getPresenter()));
        this->linkLineEdit->setText(QString::fromStdString(tutorial.getLink()));
        this->minutesLineEdit->setText(QString::fromStdString(std::to_string(tutorial.getDuration().first)));
        this->secondsLineEdit->setText(QString::fromStdString(std::to_string(tutorial.getDuration().second)));
        this->likesLineEdit->setText(QString::fromStdString(std::to_string(tutorial.getLikes())));

    });

    // Slot for Add Button
    QObject::connect(this->addButton, &QPushButton::clicked, [this]() {

        try {
            std::string title = this->titleLineEdit->text().toStdString();
            Validator::validateTitle(title);
            std::string presenter = this->presenterLineEdit->text().toStdString();
            Validator::validatePresenter(presenter);
            std::string link = this->linkLineEdit->text().toStdString();
            Validator::validateLink(link);

            std::string minutesStr = this->minutesLineEdit->text().toStdString();
            int minutes = this->validator.validateMinutes(minutesStr);
            std::string secondsStr = this->secondsLineEdit->text().toStdString();
            int seconds = this->validator.validateSeconds(secondsStr);
            std::pair<int, int> duration(minutes, seconds);
            std::string likesStr = this->likesLineEdit->text().toStdString();
            int likes = this->validator.validateLikes(likesStr);

            this->controllerAdmin.addElement(title, presenter, duration, likes, link);
            this->populateTutorialList();
            int lastTutorialIndex = this->controllerAdmin.getRepo().getLength() - 1;
            this->tutorialListWidget->setCurrentRow(lastTutorialIndex);
        }
        catch(ControllerException& e) {
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }
        catch(ValidatorException& e) {
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }

    });

    // Slot for Delete Button
    QObject::connect(this->deleteButton, &QPushButton::clicked, [this]() {

        try {
            std::string title = this->titleLineEdit->text().toStdString();
            Validator::validateTitle(title);
            std::string presenter = this->presenterLineEdit->text().toStdString();
            Validator::validatePresenter(presenter);

            this->controllerAdmin.deleteElement(title, presenter);
            this->populateTutorialList();
            int lastTutorialIndex = this->controllerAdmin.getRepo().getLength()-1;
            this->tutorialListWidget->setCurrentRow(lastTutorialIndex);
        }
        catch(ValidatorException& e){
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }
        catch(ControllerException& e){
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }

    });

    // Slot for Update Button
    QObject::connect(this->updateButton, &QPushButton::clicked, [this]() {

        try {
            std::string title = this->titleLineEdit->text().toStdString();
            Validator::validateTitle(title);
            std::string presenter = this->presenterLineEdit->text().toStdString();
            Validator::validatePresenter(presenter);
            std::string newLikesStr = this->likesLineEdit->text().toStdString();
            int newLikes = this->validator.validateLikes(newLikesStr);

            this->controllerAdmin.updateElement(title, presenter, newLikes);
            this->populateTutorialList();
            int lastTutorialIndex = this->controllerAdmin.getRepo().getLength()-1;
            this->tutorialListWidget->setCurrentRow(lastTutorialIndex);
        }
        catch(ValidatorException& e){
            QMessageBox msgBox{this};
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }
        catch(ControllerException& e){
            QMessageBox msgBox{this};
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }

    });

    // Slot for Bar Chart Button
    QObject::connect(this->seeChartButton, &QPushButton::clicked, [this]() {
        this->createChart();
    });

    // Slot for Undo Button
    QObject::connect(this->undoButton, &QPushButton::clicked, [this]() {
        try {
            this->controllerAdmin.undo();
            this->populateTutorialList();
        }
        catch (ControllerException& e) {
            QMessageBox msgBox{this};
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }
    });

    // Slot for Redo Button
    QObject::connect(this->redoButton, &QPushButton::clicked, [this](){
       try {
           this->controllerAdmin.redo();
           this->populateTutorialList();
       }
       catch (ControllerException& e) {
           QMessageBox msgBox{this};
           msgBox.setText(QString::fromStdString(e.error()));
           msgBox.exec();
       }
    });
}

int adminGUI::getIndex() const{
    QModelIndexList selectedIndexes = this->tutorialListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.empty()) {
        this->titleLineEdit->clear();
        this->presenterLineEdit->clear();
        this->linkLineEdit->clear();
        this->minutesLineEdit->clear();
        this->secondsLineEdit->clear();
        this->likesLineEdit->clear();
        return -1;
    }
    return selectedIndexes.at(0).row();
}

void adminGUI::createChart() {
    this->chartWindow = new QWidget{};
    int x =(int)(this->chartWindow->width() * 1.25);
    int y = (int)(chartWindow->height() * 1.25);
    this->chartWindow->resize(x, y);

    auto chartLayout = new QVBoxLayout(this->chartWindow);

    auto *series = new QBarSeries();
    for(const auto& tutorial: this->controllerAdmin.getRepo().getData()) {
        auto *set = new QBarSet(QString::fromStdString(tutorial.getTitle()));
        *set << tutorial.getLikes();
        series->append(set);
    }

    auto *chart = new QChart{};
    chart->addSeries(series);
    chart->setTitle("Chart based on the number of likes");
    chart->setAnimationOptions(QChart::SeriesAnimations);

//    QStringList categories;
//    for(const auto& tutorial: this->controllerAdmin.getRepo().getData()) {
//        categories << QString::fromStdString(tutorial.getTitle());
//    }

//    auto *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
//    chart->addAxis(axisX, Qt::AlignBottom);

    auto *axisY = new QValueAxis();
    axisY->setTitleText("Number of likes");
    axisY->setRange(0, 1000);
    chart->addAxis(axisY, Qt::AlignLeft);

    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartLayout->addWidget(chartView);
    this->chartWindow->show();
}

adminGUI::~adminGUI() {
    delete this->chartWindow;
}
