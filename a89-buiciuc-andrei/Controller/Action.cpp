#include "Action.h"

ActionAdd::ActionAdd(FileRepository* repository, const Tutorial& tutorial) {
    this->repository = repository;
    this->tutorial = tutorial;
}

void ActionAdd::undo() {
    int position = this->repository->findElement(this->tutorial.getTitle(), this->tutorial.getPresenter());
    this->repository->deleteElement(position);
}

void ActionAdd::redo() {
    this->repository->addElement(this->tutorial);
}

ActionDelete::ActionDelete(FileRepository* repository, const Tutorial &tutorial) {
    this->repository = repository;
    this->tutorial = tutorial;
}

void ActionDelete::undo() {
    this->repository->addElement(this->tutorial);

}

void ActionDelete::redo() {
    int position = this->repository->findElement(this->tutorial.getTitle(), this->tutorial.getPresenter());
    this->repository->deleteElement(position);
}

ActionUpdate::ActionUpdate(FileRepository* repository, const Tutorial &oldTutorial,
                           const Tutorial &newTutorial) {
    this->repository = repository;
    this->oldTutorial = oldTutorial;
    this->newTutorial = newTutorial;
}

void ActionUpdate::undo() {
    int position = this->repository->findElement(this->newTutorial.getTitle(), this->newTutorial.getPresenter());
    this->repository->updateElement(position, this->oldTutorial.getLikes());
}

void ActionUpdate::redo() {
    int position = this->repository->findElement(this->oldTutorial.getTitle(), this->oldTutorial.getPresenter());
    this->repository->updateElement(position, this->newTutorial.getLikes());
}