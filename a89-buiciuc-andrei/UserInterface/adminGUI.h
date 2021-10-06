#pragma once
#include <QWidget>
#include <QListWidget>
#include "GUI.h"

class adminGUI: public QWidget {
    Q_OBJECT
private:
    ControllerAdmin controllerAdmin;
    Validator validator;

    // Graphical elements.
    QPalette mainPalette{};
    QListWidget *tutorialListWidget{};
    QLineEdit *titleLineEdit{}, *presenterLineEdit{}, *linkLineEdit{},
                *minutesLineEdit{}, *secondsLineEdit{}, *likesLineEdit{};
    QPushButton *addButton{}, *deleteButton{}, *updateButton{}, *seeChartButton{}, *undoButton{}, *redoButton{};
    QWidget *chartWindow{};

    void initGUI(const QPalette& palette);
    void populateTutorialList();
    void connectSignalsSlots();
    void createChart();
    int getIndex() const;

public:

    adminGUI(const ControllerAdmin& controllerAdmin, const Validator& validator, const QPalette& palette);

    ~adminGUI() override;
};
