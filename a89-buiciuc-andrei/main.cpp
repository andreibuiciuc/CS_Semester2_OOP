#include "Repository/repository.h"
#include "Controller/controllerAdmin.h"
#include "UserInterface/UI.h"
#include <iostream>
#include <QApplication>
#include "GUI.h"
#include <crtdbg.h>

int main(int argc, char* argv[])
{
    FileRepository repository(R"(D:\OOP Assignements\Assignmnents\a89-911-buiciuc-andrei\tutorials.txt)");
    Repository watchlist;
    Validator validator;
    ControllerAdmin controllerAdmin(repository);
    ControllerUser controllerUser(repository, watchlist);

    bool done = false;
    std::string choice;
    while(!done) {
        std::cout << "\nEnter the User Interface type [UI / GUI] : " << '\n';
        getline(std::cin, choice);
        if(choice == "UI" || choice == "GUI") {
            done = true;
        }
        else {
            std::cout << "Bad command. Try again." << '\n';
        }
    }

    if(choice == "UI") {
        // UI
        UserInterface ui(controllerAdmin, controllerUser, validator);
        ui.start();
    }
    else {
        QApplication a(argc, argv);

        GUI gui{controllerAdmin, controllerUser, validator};
        gui.show();

        return QApplication::exec();
    }

    return 0;
}
