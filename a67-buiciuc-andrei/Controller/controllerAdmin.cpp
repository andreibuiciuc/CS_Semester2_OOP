#include "controllerAdmin.h"
#include "../Exception/customException.h"
#include <algorithm>

ControllerAdmin::ControllerAdmin() = default;

ControllerAdmin::ControllerAdmin(const FileRepository& repository) {
    this->repository = repository;
}

ControllerAdmin::ControllerAdmin(const ControllerAdmin &c) {
    this->repository = c.repository;
}

ControllerAdmin::~ControllerAdmin() = default;

const Repository& ControllerAdmin::getRepo() { return this->repository; }

int ControllerAdmin::findElement(const std::string& title, const std::string& presenter){
    int index = 0;
    for(const auto& element: this->repository.getData()) {
        if(element.getTitle() == title && element.getPresenter() == presenter) {
            break;
        }
        index ++;
    }

    if(index == this->repository.getLength()) {
        return -1;
    }

    return index;
}

void ControllerAdmin::addElement(const std::string& title, const std::string& presenter, std::pair<int,int>duration,
                           int likes, const std::string& link){

    Tutorial tutorial(title, presenter, duration, likes, link);
    int index = this->findElement(title, presenter);
    if(index == -1) {
        // Element does not exist, so it can be added.
        this->repository.addElement(tutorial);
    }
    else {
        // Element already exists, so it can not be added.
        throw ControllerException("Element already exists.");
    }
}

void ControllerAdmin::deleteElement(const std::string& title, const std::string& presenter){
    int index = this->findElement(title, presenter);
    if(index == -1) {
        // Element does not exist, so it cannot be deleted.
        throw ControllerException("Element does not exist.");
    }
    else {
        // Element exists, so it can be deleted.
        this->repository.deleteElement(index);
    }
}

void ControllerAdmin::updateElement(const std::string& title, const std::string& presenter, int newLikes){
    int index = this->findElement(title, presenter);
    if(index == -1) {
        // Element does not exist, so it cannot be updated.
        throw ControllerException("Element does not exist.");
    }
    else {
        // Element exist, so it can be updated.
        this->repository.updateElement(index, newLikes);
    }
}
