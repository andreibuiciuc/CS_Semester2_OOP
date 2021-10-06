#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QTableView>
#include "../Controller/controllerUser.h"
#include "../Validator/validator.h"
#include "../Repository/AbstractWatchlist.h"
#include "TutorialsTableModel.h"

class userGUI: public QWidget {
    Q_OBJECT
private:
    ControllerUser controllerUser;
    Validator validator;
    ControllerAdmin controllerAdmin;
    AbstractWatchlist* abstractWatchlist;

    int currentIndexTutorials{};
    int currentIndexWatchlist{};
    std::vector<Tutorial> filteredData;

    // Graphical elements
    QPalette mainPalette;
    QListWidget *tutorialListWidget{}, *watchlistWidget{};
    QLineEdit *presenterLineEdit{};
    QPushButton *searchButton{}, *addButton{}, *deleteButton{}, *exportButton{};

    TutorialsTableModel *watchlistTableModel;
    QTableView *watchlistTableView;

    void initGUI(const QPalette& palette);
    void connectSignalsSlots();
    int getIndexTutorialList() const;
    int getIndexWatchlist() const;
    void populateWatchlist();
    void populateTutorialList(const std::string& presenter);

public:

    userGUI(const ControllerUser& controllerUser, const ControllerAdmin& controllerAdmin,
            const Validator& validator, const QPalette& palette, AbstractWatchlist* abstractWatchlist);

    ~userGUI() override;
};
