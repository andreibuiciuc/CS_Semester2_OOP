#pragma once

#include "../Repository/fileRepository.h"
#include "../Domain/tutorial.h"

class Action {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class ActionAdd: public Action {
private:
    FileRepository* repository;
    Tutorial tutorial;

public:

    ActionAdd(FileRepository* repository, const Tutorial& tutorial);

    void undo() override;

    void redo() override;
};

class ActionDelete: public Action {
private:
    FileRepository* repository;
    Tutorial tutorial;

public:
    ActionDelete(FileRepository* repository, const Tutorial& tutorial);

    void undo() override;

    void redo() override;
};

class ActionUpdate: public Action {
private:
    FileRepository* repository;
    Tutorial oldTutorial;
    Tutorial newTutorial;

public:
    ActionUpdate(FileRepository* repository, const Tutorial& oldTutorial, const Tutorial& newTutorial);

    void undo() override;

    void redo() override;
};
