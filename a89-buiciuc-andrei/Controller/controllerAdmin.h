#pragma once
#include "../Repository/repository.h"
#include "../Domain/tutorial.h"
#include "../Repository/fileRepository.h"
#include "Action.h"

class ControllerAdmin{
private:
    FileRepository repository;

    std::vector<Action*> undoStack;
    std::vector<Action*> redoStack;

public:

    /// Implicit constructor.
    ControllerAdmin();

    /// Explicit constructor.
    explicit ControllerAdmin(const FileRepository& repository);

    ControllerAdmin(const ControllerAdmin& c);

    /// Destructor
    ~ControllerAdmin();

    /// Find the index position of an element.
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: the index position of the element, -1 otherwise
    int findElement(const std::string& title, const std::string& presenter);

    /// Adds an element
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \param duration: a given duration
    /// \param likes: a given number of likes
    /// \param link: a given link
    /// \return: 0 for success, 1 for failure
    void addElement(const std::string& title, const std::string& presenter, std::pair<int,int>duration, int likes, const std::string& link);

    /// Deletes an element
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: 0 for success, 1 for failure
    void deleteElement(const std::string& title, const std::string& presenter);

    /// Updates an element
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: 0 for success, 1 for failure
    void updateElement(const std::string& title, const std::string& presenter, int newLikes);

    FileRepository getRepo();

    void undo();

    void redo();
};