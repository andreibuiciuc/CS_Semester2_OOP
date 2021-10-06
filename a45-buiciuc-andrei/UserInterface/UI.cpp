#include "UI.h"
#include <iostream>
#include <windows.h>

using namespace std;

UserInterface::UserInterface(Controller* controller, Validator* validator) {
    this->controller = controller;
    this->validator = validator;
}

UserInterface::~UserInterface() {}

void UserInterface::printModes() {
    cout << "\n\nHello and welcome to Master C++. Choose the application mode: " << '\n';
    cout << "1. Administrator mode." << '\n';
    cout << "2. User mode." << '\n';
    cout << "0. Exit." << '\n';
}

void UserInterface::printAdministratorMenu() {
    cout << "\nYou are in Administrator Mode. Choose a command below: " << '\n';
    cout << "1. Add a tutorial." << '\n';
    cout << "2. Delete a tutorial." << '\n';
    cout << "3. Update a tutorial." << '\n';
    cout << "4. Display all tutorials." << '\n';
    cout << "0. Exit" << '\n';
}

void UserInterface::printUserMenu() {
    cout << "\nYou are in User Mode. Choose a command below: " << '\n';
    cout << "1. See tutorials." << '\n';
    cout << "2. Delete tutorial from watchlist." << '\n';
    cout << "3. Display the watchlist." << '\n';
    cout << "0. Exit." << '\n';
}

void UserInterface::printChoices() {
    cout << "Are you interested in this tutorial?" << '\n';
    cout << "1. Yes." << '\n';
    cout << "2. No." << '\n';
    cout << "0. Exit."<< '\n';
}

void UserInterface::displayTutorials() {
    DynamicArray<Tutorial>* tutorialList = this->controller->getRepo()->getArray();

    for(int index = 0; index < tutorialList->getLength(); index ++){
        cout << tutorialList->getData()[index].str() << '\n';
    }
}

void UserInterface::addTutorialUi() {
    string title, presenter, link, minutesStr, secondsStr, likesStr;
    int minutes, seconds, likes;

    cout << "Enter the details of the tutorial for adding: " << '\n';
    cout << "Enter the title: " << '\n';
    getline(cin, title);

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);

    cout << "Enter the link to the tutorial: " << '\n';
    getline(cin, link);
    if(!validator->validateLink(link)){
        cout << "Invalid link input." << '\n';
        return;
    }

    cout << "Enter the number of minutes: " << '\n';
    getline(cin, minutesStr);
    minutes = this->validator->validateMinutes(minutesStr);
    if(minutes == -1){
        cout << "Invalid minutes input." << '\n';
        return;
    }

    cout << "Enter the number of seconds: " << '\n';
    getline(cin, secondsStr);
    seconds = this->validator->validateSeconds(secondsStr);
    if(seconds == -1){
        cout << "Invalid seconds input." << '\n';
        return;
    }

    cout << "Enter the number of likes: " << '\n';
    getline(cin, likesStr);
    likes = this->validator->validateLikes(likesStr);
    if(likes == -1){
        cout << "Invalid number of likes input." << '\n';
        return;
    }

    pair<int,int>duration(minutes,seconds);
    if(this->controller->addElement(title, presenter, duration, likes, link) == 1){
        cout << "Element already exists." << '\n';
    }
}

void UserInterface::deleteTutorialUi() {
    string title, presenter;

    cout << "Enter the details of the tutorial for removal: " << '\n';
    cout << "Enter the title: " << '\n';
    getline(cin, title);
    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);

    if(this->controller->deleteElement(title, presenter) == 1){
        cout << "Tutorial does not exist." << '\n';
    }
}

void UserInterface::updateTutorialUi() {
    string title, presenter, newLikesStr;
    int newLikes;

    cout << "Enter the details of the tutorial for update: " << '\n';
    cout << "Enter the title: " << '\n';
    getline(cin, title);

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);

    cout << "Enter the new number of likes: " << '\n';
    getline(cin, newLikesStr);

    newLikes = this->validator->validateLikes(newLikesStr);
    if(newLikes == -1){
        cout << "Invalid number of likes input." << '\n';
        return;
    }

    if(this->controller->updateElement(title, presenter, newLikes) == 1){
        cout << "Tutorial does not exist." << '\n';
    }
}

void UserInterface::administratorMode() {
    this->printAdministratorMenu();
    bool done = false;
    string adminCommandStr;
    int adminCommand;

    while (!done) {
        cout << "\nEnter your command: " << '\n';
        getline(cin, adminCommandStr);
        adminCommand = this->validator->validateCommand(adminCommandStr);

        if (adminCommand == 1)
            this->addTutorialUi();
        else if (adminCommand == 2)
            this->deleteTutorialUi();
        else if (adminCommand == 3)
            this->updateTutorialUi();
        else if (adminCommand == 4)
            this->displayTutorials();
        else if (adminCommand == 0)
            done = 1;
        else
            cout << "Bad command" << '\n';
    }

    this->printModes();
}


void UserInterface::seeTutorials()  {
    int index = 0, choice, numberTutorials;
    bool done = false;
    string presenter, choiceStr;

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);

    DynamicArray<Tutorial>* filteredTutorials = new DynamicArray<Tutorial>(100);


    numberTutorials = this->controller->filterTutorialsByPresenter(filteredTutorials, presenter);


    while(!done) {
        cout << '\n' << filteredTutorials->getData()[index].str() << '\n';
        string url = filteredTutorials->getData()[index].get_link();
        ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);

        this->printChoices();
        cout << "Enter your choice: " << '\n';
        getline(cin, choiceStr);
        choice = this->validator->validateCommand(choiceStr);

        if(choice == 1) {
            if(this->controller->addToWatchlist(filteredTutorials->getData()[index]) == 1) {
                cout << "Tutorial already in your watchlist." << '\n';
            }
            index = index + 1;
        }
        else if(choice == 2)
            index = index + 1;
        else if(choice == 0)
            done = true;
        else
            cout << "Bad command." << '\n';

        if(index == numberTutorials)
            index = 0;
    }

    delete filteredTutorials;
}

void UserInterface::displayWatchList() {
    DynamicArray<Tutorial>* watchlist = this->controller->getWatchlist();
    for(int index = 0; index < watchlist->getLength(); index ++) {
        cout << watchlist->getData()[index].str() << '\n';
    }
}

void UserInterface::deleteTutorialWatchList() {
    string title, presenter, choiceStr;
    int choice, likes, position;

    cout << "Enter the title: " << '\n';
    getline(cin, title);
    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);


    position = this->controller->deleteTutorialFromWatchlist(title, presenter);
    if (position == 1) {
        cout << "Tutorial does not exist in the watchlist." << '\n';
    } else {
        cout << "Did you like this tutorial? Leave a like." << '\n';
        cout << "1. Yes." << '\n';
        cout << "0. No." << '\n';
        getline(cin, choiceStr);

        choice = this->validator->validateCommand(choiceStr);
        if(choice == 1) {
            position = this->controller->findElement(title, presenter);
            likes = this->controller->getRepo()->getArray()->getData()[position].get_likes();
            likes += 1;
            this->controller->updateElement(title, presenter, likes);
        }
    }
}

void UserInterface::userMode() {
    string commandStr;
    int command;
    bool done = false;

    this->printUserMenu();

    while(!done) {
        cout << "Enter your command: " << '\n';
        getline(cin, commandStr);
        command = this->validator->validateCommand(commandStr);

        if (command == 1)
            this->seeTutorials();
        else if (command == 2)
            this->deleteTutorialWatchList();
        else if (command == 3)
            this->displayWatchList();
        else if (command == 0)
            done = true;
        else
            cout << "Bad command." << '\n';
    }
}

void UserInterface::start() {
    string appModeStr;
    int appMode = 0;
    bool doneApp = false;
    this->printModes();


    while(!doneApp) {
        cout << "\nEnter the application mode: " << '\n';
        getline(cin, appModeStr);
        appMode = this->validator->validateCommand(appModeStr);

        if(appMode == 1)
            this->administratorMode();
        else if(appMode == 2)
            this->userMode();
        else if(appMode == 0)
            doneApp = true;
        else
            cout << "Bad command." << '\n';
    }
}
