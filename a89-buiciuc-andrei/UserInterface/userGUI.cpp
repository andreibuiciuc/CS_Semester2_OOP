#include <QHBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include "userGUI.h"
#include "../Exception/customException.h"
#include <windows.h>

userGUI::userGUI(const ControllerUser& controllerUser, const ControllerAdmin& controllerAdmin,
                 const Validator& validator, const QPalette& palette, AbstractWatchlist* abstractWatchlist) {
    this->controllerUser = controllerUser;
    this->controllerAdmin = controllerAdmin;
    this->validator = validator;
    this->abstractWatchlist = abstractWatchlist;
    this->mainPalette = palette;
    this->initGUI(this->mainPalette);
    this->connectSignalsSlots();
}

void userGUI::initGUI(const QPalette &palette) {
    int x = (int)(this->width() * 1.25);
    int y = (int)(this->height() * 1.25);
    this->resize(x, y);

    this->setPalette(this->mainPalette);

    this->tutorialListWidget = new QListWidget{};

    // View / Model components
    this->watchlistTableModel = new TutorialsTableModel{this->controllerAdmin.getRepo()};
    this->watchlistTableView = new QTableView{};
    this->watchlistTableView->resizeRowsToContents();
    this->watchlistTableView->resizeColumnsToContents();
    this->watchlistTableView->setModel(this->watchlistTableModel);

    this->presenterLineEdit = new QLineEdit{};
    this->searchButton = new QPushButton{"Search"};
    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->exportButton = new QPushButton{"Export watchlist"};

    auto *userLayout = new QGridLayout{this};
    userLayout->addWidget(this->tutorialListWidget, 0, 0);
//    userLayout->addWidget(this->watchlistWidget, 0, 1);
//    userLayout->addWidget(this->tutorialListTableView, 0, 0);
    userLayout->addWidget(this->watchlistTableView, 0, 1);

    auto *tutorialLayout = new QFormLayout{};
    tutorialLayout->addRow("Presenter", this->presenterLineEdit);
    userLayout->addLayout(tutorialLayout, 1, 0, 1, 2);

    userLayout->addWidget(this->searchButton, 2, 0, 1, 2);
    userLayout->addWidget(this->addButton, 3, 0);
    userLayout->addWidget(this->deleteButton, 3, 1);
    userLayout->addWidget(this->exportButton, 4, 0, 1, 2);
}

void userGUI::populateWatchlist() {
    this->watchlistWidget->clear();

    std::vector<Tutorial> watchlistData = this->controllerUser.getWatchlist().getData();
    for(const auto& tutorial: watchlistData) {
        this->watchlistWidget->addItem(QString::fromStdString(tutorial.getTitle() + " | " + tutorial.getPresenter()));
    }
}

void userGUI::populateTutorialList(const std::string& presenter) {
    this->tutorialListWidget->clear();

    this->controllerUser.filterTutorialsByPresenter(this->filteredData, presenter);
    for(const auto& tutorial: this->filteredData) {
        this->tutorialListWidget->addItem(QString::fromStdString(tutorial.getTitle() + " | " + tutorial.getPresenter()));
    }
}

void userGUI::connectSignalsSlots() {
    // Slot for Search Button
    QObject::connect(this->searchButton, &QPushButton::clicked, [this]() {
        std::string presenter = this->presenterLineEdit->text().toStdString();
        this->populateTutorialList(presenter);
    });

    // Slot for item selection in the tutorials list
    QObject::connect(this->tutorialListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getIndexTutorialList();
        if(selectedIndex == -1) {
            return;
        }
        this->currentIndexTutorials = selectedIndex;
    });

    // Slot for item selection in the watchlist.
    QObject::connect(this->watchlistWidget, &QListWidget::itemSelectionChanged, [this]() {
         int selectedIndex = this->getIndexWatchlist();
         if(selectedIndex == -1) {
             return;
         }
         this->currentIndexWatchlist = selectedIndex;
    });

    // Slot for double click on tutorial in the watchlist
    QObject::connect(this->watchlistWidget, &QListWidget::doubleClicked, [this]() {
        int selectedIndex = this->getIndexWatchlist();
        if(selectedIndex == -1) {
            return;
        }
        this->currentIndexWatchlist = selectedIndex;
        std::string url = this->controllerUser.getWatchlist().getData()[selectedIndex].getLink();
        ShellExecute(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    });

    // Slot for Add Button
    QObject::connect(this->addButton, &QPushButton::clicked, [this]() {
        if(this->currentIndexTutorials == -1 || this->filteredData.empty()) {
            return;
        }
        try {
            Tutorial tutorial = this->filteredData[this->currentIndexTutorials];
            this->controllerUser.addToWatchlist(tutorial);
            this->populateWatchlist();
        }
        catch(ControllerException& e) {
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(e.error()));
            msgBox.exec();
        }
    });

    // Slot for Delete Button
    QObject::connect(this->deleteButton, &QPushButton::clicked, [this]() {
        if(this->currentIndexWatchlist == -1 || this->controllerUser.getWatchlist().getLength() == 0) {
            return;
        }

        Tutorial tutorial = this->controllerUser.getWatchlist().getData()[this->currentIndexWatchlist];
        QMessageBox msgBox;
        msgBox.setText("Thank you for watching this tutorial.");
        msgBox.setInformativeText("Leave a like if you enjoyed it.");

        QPushButton *likeButton = msgBox.addButton("Like",QMessageBox::YesRole);
        QPushButton *exitButton = msgBox.addButton("Exit", QMessageBox::NoRole);

        msgBox.exec();

        if(msgBox.clickedButton() == likeButton) {
            int newLikes = tutorial.getLikes() + 1;
            this->controllerAdmin.updateElement(tutorial.getTitle(), tutorial.getPresenter(), newLikes);
            msgBox.close();
        }
        if(msgBox.clickedButton() == exitButton) {
            msgBox.close();
        }

        this->controllerUser.deleteTutorialFromWatchlist(tutorial.getTitle(), tutorial.getPresenter());
        this->populateWatchlist();
        this->currentIndexWatchlist = -1;
    });

    // Slot for Export Button
    QObject::connect(this->exportButton, &QPushButton::clicked, [this]() {
        this->abstractWatchlist->process(this->controllerUser.getWatchlist().getData());
    });
}

int userGUI::getIndexTutorialList() const{
    QModelIndexList selectedIndexes = this->tutorialListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.empty()) {
        return -1;
    }
    return selectedIndexes.at(0).row();
}

int userGUI::getIndexWatchlist() const {
    QModelIndexList selectedIndexes = this->watchlistWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.empty()) {
        return -1;
    }
    return selectedIndexes.at(0).row();
}

userGUI::~userGUI() = default;

