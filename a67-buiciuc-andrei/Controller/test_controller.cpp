//#include "test_controller.h"
//#include "controllerAdmin.h"
//#include "controllerUser.h"
//#include <cassert>
//#include <iostream>
//
//void test_controller(){
//    Repository repository;
//    Repository watchlist;
//    ControllerAdmin controller(repository);
//    assert(controller.getRepo().getLength()== 0);
//
//    std::pair<int,int>p1(20,30);
//    controller.addElement("And", "Bui", p1, 1000, "asd");
//    assert(controller.getRepo().getLength() == 1);
//
//    std::pair<int,int>p2(30,40);
//    controller.addElement("Qwe", "rty", p2, 0, "qwerty");
//    assert(controller.getRepo().getLength() == 2);
//
//    controller.deleteElement("Qwe", "rty");
//    controller.deleteElement("And", "Bui");
//    assert(controller.getRepo().getLength() == 0);
//
//    controller.addElement("And", "Bui", p1, 1000, "asd");
//    assert(controller.getRepo().getLength() == 1);
//
//    controller.updateElement("And", "Bui", 2000);
//    assert(controller.getRepo().getData()[0].getLikes() == 2000);
//
//    int pos1 = controller.findElement("And", "Bui");
//    assert(pos1 == 0);
//    int pos2 = controller.findElement("Qwe", "rty");
//    assert(pos2 == -1);
//
//    int res1 = controller.addElement("And", "Bui", p1, 1000, "asd");
//    assert(res1 == -1);
//
//    int res2 = controller.deleteElement("Qwe", "rty");
//    assert(res2 == -1);
//
//    int res3 = controller.updateElement("Qwe", "rty", 100);
//    assert(res3 == -1);
//}
//
//void testWatchlist(){
//    Repository repository;
//    Repository watchlist;
//    ControllerAdmin controller(repository);
//    ControllerUser controllerUser(repository, watchlist);
//
//    std::pair<int,int>p1(20,30);
//    controller.addElement("And", "Bui", p1, 1000, "asd");
//
//    std::pair<int,int>p2(30,40);
//    controller.addElement("Qwe", "rty", p2, 0, "qwerty");
//
//    controllerUser.addToWatchlist(controller.getRepo().getData()[0]);
//    controllerUser.addToWatchlist(controller.getRepo().getData()[1]);
//
//    assert(controller.getRepo().getLength() == 2);
//    assert(controllerUser.getWatchlist().getLength() == 2);
//
//    int r = controllerUser.addToWatchlist(controller.getRepo().getData()[0]);
//    assert(r == -1);
//
//    int pos1 = controllerUser.findTutorialInWatchlist("And", "Bui");
//    assert(pos1 == 0);
//    int pos2 = controllerUser.findTutorialInWatchlist("Qwe", "rty");
//    assert(pos2 == 1);
//    int pos3 = controllerUser.findTutorialInWatchlist("asd","asd");
//    assert(pos3 == -1);
//
//}
