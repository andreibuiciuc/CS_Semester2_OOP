#pragma once
#include "../Controller/controllerAdmin.h"
#include "../Validator/validator.h"
#include "../Controller/controllerUser.h"
#include "../Repository/AbstractWatchlist.h"

class UserInterface{
    private:
        ControllerAdmin controllerAdmin;
        ControllerUser controllerUser;
        Validator validator;
        AbstractWatchlist* absWatchlist{};

    static void printModes();

    static void printAdministratorMenu();

    static void printUserMenu();

    static void printChoices();

    static void printOut();

    void displayTutorials();

    void addTutorialUi();

    void deleteTutorialUi();

    void updateTutorialUi();

    void administratorMode();

    void seeTutorials();

    void displayWatchlist();

    void openWatchlist();

    void deleteTutorialWatchlist();

    void userMode();

public:
    UserInterface(const ControllerAdmin& controllerAdmin, const ControllerUser& controllerUser,
                  const Validator& validator);

    ~UserInterface();

    void start();
};