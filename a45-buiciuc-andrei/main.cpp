#include <iostream>
#include "Domain/test_domain.h"
#include "Repository/test_dynamic_array.h"
#include "Repository/test_repository.h"
#include "Controller/test_controller.h"
#include "Validator/test_validator.h"
#include "UserInterface/UI.h"

int main()
{
    test_tutorial();
    std::cout << "Test tutorial done." << '\n';
    test_dynamic_array();
    std::cout << "Test dynamic array done." << '\n';
    test_repository();
    std::cout << "Test repository done." << '\n';
    test_controller();
    testWatchlist();
    std::cout << "Test controller done." << '\n';
    test_validator();
    std::cout << "Test validator done." << '\n';


    DynamicArray<Tutorial>* dynamicArray = new DynamicArray<Tutorial>(100);
    DynamicArray<Tutorial>* watchlist = new DynamicArray<Tutorial>(100);
    Repository* repository = new Repository(dynamicArray);
    repository->initRepository();
    Controller* controller = new Controller(repository, watchlist);
    Validator* validator = new Validator();
    UserInterface* ui = new UserInterface(controller, validator);
    ui->start();

    delete dynamicArray;
    delete watchlist;
    delete repository;
    delete controller;
    delete validator;
    delete ui;



    // _CrtDumpMemoryLeaks();
    return 0;
}