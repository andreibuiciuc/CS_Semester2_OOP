#pragma once
#include "../Controller/controller.h"
#include "../Validator/validator.h"

class UserInterface{
    private:
        Controller* controller;
        Validator* validator;

    public:

    UserInterface(Controller* controller, Validator* validator);

    ~UserInterface();

    static void printModes();

    static void printAdministratorMenu();

    static void printUserMenu();

    static void printChoices();

    void displayTutorials();

    void addTutorialUi();

    void deleteTutorialUi();

    void updateTutorialUi();

    void administratorMode();

    void seeTutorials();

    void displayWatchList();

    void deleteTutorialWatchList();

    void userMode();

    void start();

};