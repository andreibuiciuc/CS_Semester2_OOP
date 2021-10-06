#include "test_controller.h"
#include "controller.h"
#include <assert.h>

void test_controller(){
    DynamicArray<Tutorial>* array = new DynamicArray<Tutorial>(1);
    DynamicArray<Tutorial>* watchlist = new DynamicArray<Tutorial>(1);
    Repository* repository = new Repository(array);
    Controller* controller = new Controller(repository, watchlist);
    assert(controller->getRepo()->getArray()->getLength() == 0);
    assert(controller->getRepo()->getArray()->getCapacity() == 1);


    std::pair<int,int>p1(20,30);
    controller->addElement("And", "Bui", p1, 1000, "asd");
    assert(controller->getRepo()->getArray()->getLength() == 1);
    assert(controller->getRepo()->getArray()->getCapacity() == 1);

    std::pair<int,int>p2(30,40);
    controller->addElement("Qwe", "rty", p2, 0, "qwerty");
    assert(controller->getRepo()->getArray()->getLength() == 2);
    assert(controller->getRepo()->getArray()->getCapacity() == 2);

    controller->deleteElement("Qwe", "rty");

    controller->deleteElement("And", "Bui");
    assert(controller->getRepo()->getArray()->getLength() == 0);
    assert(controller->getRepo()->getArray()->getCapacity() == 2);

    controller->addElement("And", "Bui", p1, 1000, "asd");
    assert(controller->getRepo()->getArray()->getLength() == 1);
    assert(controller->getRepo()->getArray()->getCapacity() == 2);

    controller->updateElement("And", "Bui", 2000);
    assert(controller->getRepo()->getArray()->getData()[0].get_likes() == 2000);

    int pos1 = controller->findElement("And", "Bui");
    assert(pos1 == 0);
    int pos2 = controller->findElement("Qwe", "rty");
    assert(pos2 == -1);

    int res1 = controller->addElement("And", "Bui", p1, 1000, "asd");
    assert(res1 == 1);

    int res2 = controller->deleteElement("Qwe", "rty");
    assert(res2 == 1);

    int res3 = controller->updateElement("Qwe", "rty", 100);
    assert(res3 == 1);

    delete array;
    delete watchlist;
    delete repository;
    delete controller;
}

void testWatchlist(){
    DynamicArray<Tutorial>* array = new DynamicArray<Tutorial>(5);
    DynamicArray<Tutorial>* watchlist = new DynamicArray<Tutorial>(5);
    Repository* repo = new Repository(array);
    Controller* controller = new Controller(repo, watchlist);

    std::pair<int,int>p1(20,30);
    controller->addElement("And", "Bui", p1, 1000, "asd");

    std::pair<int,int>p2(30,40);
    controller->addElement("Qwe", "rty", p2, 0, "qwerty");

    controller->addToWatchlist(controller->getRepo()->getArray()->getData()[0]);
    controller->addToWatchlist(controller->getRepo()->getArray()->getData()[1]);
    assert(controller->getWatchlist()->getLength() == 2);

    int r = controller->addToWatchlist(controller->getRepo()->getArray()->getData()[0]);
    assert(r == 1);

    int pos1 = controller->findTutorialInWatchlist("And", "Bui");
    assert(pos1 == 0);
    int pos2 = controller->findTutorialInWatchlist("Qwe", "rty");
    assert(pos2 == 1);
    int pos3 = controller->findTutorialInWatchlist("asd","asd");
    assert(pos3 == -1);

    DynamicArray<Tutorial>* filtered = new DynamicArray<Tutorial>(5);
    controller->filterTutorialsByPresenter(filtered, "Bui");
    assert(filtered->getLength() == 1);
    delete filtered;

    DynamicArray<Tutorial>* filtered2 = new DynamicArray<Tutorial>(5);
    controller->filterTutorialsByPresenter(filtered2, "");
    assert(filtered2->getLength() == 2);
    delete filtered2;

    controller->deleteTutorialFromWatchlist("And", "Bui");
    assert(controller->getWatchlist()->getLength() == 1);

    int r2 = controller->deleteTutorialFromWatchlist("And", "Bui");
    assert(r2 == 1);

    delete watchlist;
    delete array;
    delete repo;
    delete controller;
}
