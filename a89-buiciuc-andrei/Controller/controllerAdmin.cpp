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

void ControllerAdmin::undo() {
    if(this->undoStack.empty()) {
        throw ControllerException("No undos left.\n");
    }

    auto* currentAction = this->undoStack.back();
    currentAction->undo();
    this->redoStack.push_back(currentAction);
    this->undoStack.pop_back();
}

void ControllerAdmin::redo() {
    if(this->redoStack.empty()) {
        throw ControllerException("No redos left.\n");
    }
    auto* currentAction = this->redoStack.back();
    currentAction->redo();
    this->undoStack.push_back(currentAction);
    this->redoStack.pop_back();
}

FileRepository ControllerAdmin::getRepo() { return this->repository; }

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
        auto* action = new ActionAdd(&this->repository, tutorial);
        this->undoStack.push_back(action);
        this->redoStack.clear();
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
        Tutorial tutorial = this->getRepo().getData()[index];
        this->repository.deleteElement(index);
        auto* action = new ActionDelete(&this->repository, tutorial);
        this->undoStack.push_back(action);
        this->redoStack.clear();
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
        Tutorial oldTutorial = this->getRepo().getData()[index];
        this->repository.updateElement(index, newLikes);
        Tutorial newTutorial = this->getRepo().getData()[index];
        auto* action = new ActionUpdate(&this->repository, oldTutorial, newTutorial);
        this->undoStack.push_back(action);
        this->redoStack.clear();
    }
}
