#include "controller.h"

using namespace std;

Controller::Controller(Repository *repository, DynamicArray<Tutorial>* watchlist) {
    this->repository = repository;
    this->watchlist = watchlist;
}

Controller::~Controller() {}

Repository* Controller::getRepo() { return this->repository; }

int Controller::findElement(string title, string presenter){
    DynamicArray<Tutorial>* dynamicArray = this->repository->getArray();
    Tutorial element;
    int position = -1;

    for(int index = 0; index < dynamicArray->getLength(); index ++){
        element = dynamicArray->getData()[index];
        if(element.get_title() == title && element.get_presenter() == presenter){
            position = index;
            break;
        }
    }

    return position;
}

int Controller::addElement(string title, string presenter, pair<int,int>duration, int likes, string link){
    Tutorial element = Tutorial(title, presenter, duration, likes, link);
    int position = this->findElement(title, presenter);
    if(position == -1) {
        // Element does not exist, that means it can be added.
        this->repository->addElement(element);
        return 0;
    }
    else
    {
        // Element already exists, that means it can be added.
        return 1;
    }
}

int Controller::deleteElement(string title, string presenter){
    int position = this->findElement(title, presenter);
    if(position == -1){
        // Element does not exist, that means it cannot be deleted.
        return 1;
    }
    else
    {
        // Element exists, that means it can be deleted.
        this->getRepo()->deleteElement(position);
        return 0;
    }
}

int Controller::updateElement(string title, string presenter, int new_likes){
    int position = this->findElement(title, presenter);
    if(position == -1){
        // Element does not exist, that means it cannot be updated.
        return 1;
    }
    else{
        // Element exists, that means it can be updated.
        this->getRepo()->updateElement(position, new_likes);
        return 0;
    }
}

int Controller::filterTutorialsByPresenter(DynamicArray<Tutorial>* filteredTutorials, std::string presenter) {
    int length = 0;

    for(int i = 0; i < this->getRepo()->getArray()->getLength(); i ++) {
        if(this->getRepo()->getArray()->getData()[i].get_presenter() == presenter || presenter == "") {
            filteredTutorials->addElement(this->getRepo()->getArray()->getData()[i]);
            length = length + 1;
        }
    }

    return length;
}

int Controller::findTutorialInWatchlist(string title, string presenter) {
    int position = -1;

    for(int index = 0; index < this->watchlist->getLength(); index ++){
        if(this->watchlist->getData()[index].get_title() == title &&
            this->watchlist->getData()[index].get_presenter() == presenter) {
            position = index;
            break;
        }
    }

    return position;
}

int Controller::addToWatchlist(Tutorial tutorial) {
    int position = this->findTutorialInWatchlist(tutorial.get_title(), tutorial.get_presenter());

    if(position == -1) {
        this->watchlist->addElement(tutorial);
        return 0;
    }
    return 1;
}

int Controller::deleteTutorialFromWatchlist(string title, string presenter) {
    int position = this->findTutorialInWatchlist(title, presenter);

    if(position == -1) {
        return 1;
    }

    this->watchlist->deleteElement(position);
    return 0;
}

DynamicArray<Tutorial>* Controller::getWatchlist() {
    return this->watchlist;
}

