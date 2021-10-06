#include "UI.h"
#include "../Exception/customException.h"
#include "../Repository/AbstractWatchlist.h"
#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

UserInterface::UserInterface(const ControllerAdmin& controllerAdmin, const ControllerUser& controllerUser,
                             const Validator& validator) {
    this->controllerAdmin = controllerAdmin;
    this->controllerUser = controllerUser;
    this->validator = validator;
}

UserInterface::~UserInterface() {
    delete this->absWatchlist;
}
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
    cout << "4. Open watchlist." << '\n';
    cout << "0. Exit." << '\n';
}

void UserInterface::printChoices() {
    cout << "Are you interested in this tutorial?" << '\n';
    cout << "1. Yes." << '\n';
    cout << "2. No." << '\n';
    cout << "0. Exit."<< '\n';
}

void UserInterface::printOut() {
    cout << "\nChoose the output mode: " << '\n';
    cout << "1. CSV." << '\n';
    cout << "2. HTML." << '\n';
}

void UserInterface::displayTutorials() {
    std::vector<Tutorial>data = this->controllerAdmin.getRepo().getData();

    for(const auto& element: data){
        cout << element << '\n';
    }
}

void UserInterface::addTutorialUi() {
    string title, presenter, link, minutesStr, secondsStr, likesStr;
    int minutes, seconds, likes;

    cout << "Enter the details of the tutorial for adding: " << '\n';
    cout << "Enter the title: " << '\n';
    getline(cin, title);
    Validator::validateTitle(title);

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);
    Validator::validatePresenter(presenter);

    cout << "Enter the link to the tutorial: " << '\n';
    getline(cin, link);
    Validator::validateLink(link);

    cout << "Enter the number of minutes: " << '\n';
    getline(cin, minutesStr);
    minutes = this->validator.validateMinutes(minutesStr);

    cout << "Enter the number of seconds: " << '\n';
    getline(cin, secondsStr);
    seconds = this->validator.validateSeconds(secondsStr);

    cout << "Enter the number of likes: " << '\n';
    getline(cin, likesStr);
    likes = this->validator.validateLikes(likesStr);

    pair<int,int>duration(minutes,seconds);
    this->controllerAdmin.addElement(title, presenter, duration, likes, link);
    cout << "Tutorial has been successfully added." << '\n';
}

void UserInterface::deleteTutorialUi() {
    string title, presenter;

    cout << "Enter the details of the tutorial for removal: " << '\n';
    cout << "Enter the title: " << '\n';
    getline(cin, title);
    Validator::validateTitle(title);

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);
    Validator::validatePresenter(presenter);

    this->controllerAdmin.deleteElement(title, presenter);
    cout << "Tutorial has been successfully deleted." << '\n';
}

void UserInterface::updateTutorialUi() {
    string title, presenter, newLikesStr;
    int newLikes;

    cout << "Enter the details of the tutorial for update: " << '\n';
    cout << "Enter the title: " << '\n';
    getline(cin, title);
    Validator::validateTitle(title);

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);
    Validator::validatePresenter(presenter);

    cout << "Enter the new number of likes: " << '\n';
    getline(cin, newLikesStr);
    newLikes = this->validator.validateLikes(newLikesStr);

    this->controllerAdmin.updateElement(title, presenter, newLikes);
    cout << "Tutorial has been successfully updated." << '\n';
}

void UserInterface::administratorMode() {
    bool done = false;
    string adminCommandStr;
    int adminCommand;

    while (!done) {
        try {
            this->printAdministratorMenu();
            cout << "\nEnter your command: " << '\n';
            getline(cin, adminCommandStr);
            adminCommand = this->validator.validateCommand(adminCommandStr);

            if (adminCommand == 1)
                this->addTutorialUi();
            else if (adminCommand == 2)
                this->deleteTutorialUi();
            else if (adminCommand == 3)
                this->updateTutorialUi();
            else if (adminCommand == 4)
                this->displayTutorials();
            else if (adminCommand == 0)
                done = true;
            else
                cout << "Bad command" << '\n';
        }
        catch(ControllerException& e) {
            cout << e.error() << '\n';
        }
        catch(ValidatorException& e) {
            cout << e.error() << '\n';
        }
    }
}

void UserInterface::seeTutorials()  {
    int index = 0, choice, numberTutorials;
    bool done = false;
    string presenter, choiceStr;

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);

    std::vector<Tutorial> filteredTutorials;
    this->controllerUser.filterTutorialsByPresenter(filteredTutorials, presenter);
    numberTutorials = filteredTutorials.size();

    while(!done) {
        cout << '\n' << filteredTutorials[index] << '\n';
        string url = filteredTutorials[index].getLink();
//        ShellExecute(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

        this->printChoices();
        cout << "Enter your choice: " << '\n';
        getline(cin, choiceStr);
        choice = this->validator.validateCommand(choiceStr);

        if(choice == 1) {
            try{
                this->controllerUser.addToWatchlist(filteredTutorials[index]);
            }
            catch(ControllerException& e) {
                cout << e.error() << '\n';
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
}

void UserInterface::displayWatchlist() {
    std::vector<Tutorial>watchlist = this->controllerUser.getWatchlist().getData();
    for(const auto& element: watchlist) {
        cout << element.str() << '\n';
    }
}

void UserInterface::openWatchlist() {
    this->absWatchlist->process(this->controllerUser.getWatchlist().getData());
}

void UserInterface::deleteTutorialWatchlist() {
    string title, presenter, choiceStr;
    int choice, likes, position;

    cout << "Enter the title: " << '\n';
    getline(cin, title);
    Validator::validateTitle(title);

    cout << "Enter the presenter: " << '\n';
    getline(cin, presenter);
    Validator::validatePresenter(presenter);

    try {
        this->controllerUser.deleteTutorialFromWatchlist(title, presenter);
        cout << "Did you like this tutorial? Leave a like." << '\n';
        cout << "1. Yes." << '\n';
        cout << "0. No." << '\n';
        getline(cin, choiceStr);

        choice = this->validator.validateCommand(choiceStr);
        if (choice == 1) {
            position = this->controllerAdmin.findElement(title, presenter);
            likes = this->controllerAdmin.getRepo().getData()[position].getLikes();
            likes += 1;
            this->controllerAdmin.updateElement(title, presenter, likes);
        }
    }
    catch(ControllerException& e) {
        cout << e.error() << '\n';
    }
}

void UserInterface::userMode() {
    string commandStr;
    int command;
    bool done = false;

    while(!done) {
        try {
            this->printUserMenu();
            cout << "Enter your command: " << '\n';
            getline(cin, commandStr);
            command = this->validator.validateCommand(commandStr);
            if (command == 1)
                this->seeTutorials();
            else if (command == 2)
                this->deleteTutorialWatchlist();
            else if (command == 3)
                this->displayWatchlist();
            else if(command == 4)
                this->openWatchlist();
            else if (command == 0)
                done = true;
            else
                cout << "Bad command." << '\n';
        }
        catch(ControllerException& e) {
            cout << e.error() << '\n';
        }
        catch(ValidatorException& e) {
            cout << e.error() << '\n';
        }
    }
}

void UserInterface::start() {
    string appModeStr, outputModeStr;
    int appMode, outputMode;
    bool doneApp = false, doneMode = false;

    while(!doneMode) {
        this->printOut();
        cout << "\nEnter the output mode: " << '\n';
        getline(cin, outputModeStr);
        outputMode = this->validator.validateCommand(outputModeStr);
        if(outputMode == 1 || outputMode == 2) {
            doneMode = true;
        }
        else
            cout << "Bad command." << '\n';
    }

    AbstractWatchlist *abstractWatch;
    if (outputMode == 1) {
        abstractWatch = new CSVWatchlist(R"(D:\OOP Assignements\Assignmnents\a89-911-buiciuc-andrei\CSVWatchlist.txt)");
        this->absWatchlist = abstractWatch;
    } else {
        abstractWatch = new HTMLWatchlist(
                R"(D:\OOP Assignements\Assignmnents\a89-911-buiciuc-andrei\HTMLWatchlist.html)");
        this->absWatchlist = abstractWatch;
    }

    while (!doneApp) {
        this->printModes();
        cout << "\nEnter the application mode: " << '\n';
        getline(cin, appModeStr);
        appMode = this->validator.validateCommand(appModeStr);

        if (appMode == 1)
            this->administratorMode();
        else if (appMode == 2)
            this->userMode();
        else if (appMode == 0)
            doneApp = true;
        else
            cout << "Bad command." << '\n';
    }
}
