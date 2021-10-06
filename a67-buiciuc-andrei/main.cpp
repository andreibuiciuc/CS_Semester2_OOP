#include "Repository/repository.h"
#include "Controller/controllerAdmin.h"
#include "UserInterface/UI.h"

int main()
{
    FileRepository repository(R"(D:\OOP Assignements\Assignmnents\a67-911-buiciuc-andrei\tutorials.txt)");
    Repository watchlist;

    ControllerAdmin controllerAdmin(repository);
    ControllerUser controllerUser(repository, watchlist);
    Validator validator;

    UserInterface ui(controllerAdmin, controllerUser, validator);
    ui.start();

    return 0;
}
