#pragma once
#include <QWidget>
#include "UI.h"
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>

class GUI : public QWidget {
    Q_OBJECT
private:
    ControllerAdmin controllerAdmin;
    ControllerUser controllerUser;
    Validator validator;
    AbstractWatchlist* absWatchlist{};

    // Graphical elements.
    QPushButton *administratorModeButton{}, *userModeButton{};
    QPalette mainPalette;
    QRadioButton *radioCSV{}, *radioHTML{};
    bool isChecked;

    void initGUI();
    void connectSignals();

public:
    GUI(const ControllerAdmin& controllerAdmin, const ControllerUser& controllerUser,
        const Validator& validator);

    ~GUI() override;

    void openAdministratorMode();

    void openUserMode();
};
