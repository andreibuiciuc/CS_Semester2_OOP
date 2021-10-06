#pragma once

#include "controllerAdmin.h"

class ControllerUser {
private:
    Repository repository;
    Repository watchlist;

public:

    /// Implicit constructor.
    ControllerUser();

    /// Explicit constructor.
    explicit ControllerUser(const Repository& repository, const Repository& watchlist);

    /// Copy constructor.
    ControllerUser(const ControllerUser& controllerUser);

    /// Destructor.
    ~ControllerUser();

    /// Filters the array of tutorials by the presenter
    /// \param presenter: a given presenter
    /// \return: the length of the new array
    void filterTutorialsByPresenter(std::vector<Tutorial>& filteredTutorials, const std::string& presenter);

    /// Finds a tutorial in the watchlist.
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: the position in the watchlist, -1 otherwise
    int findTutorialInWatchlist(const std::string& title, const std::string& presenter);

    /// Adds a tutorial to the watchlist
    /// \param tutorial: a given tutorial
    /// \return: 0 if added, 1 if tutorial already in the watchlist
    void addToWatchlist(const Tutorial& tutorial);

    /// Deletes a tutorial from the watchlist
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: 0 if deleted, 1 if tutorial not in the watchlist
    void deleteTutorialFromWatchlist(const std::string& title, const std::string& presenter);

    /// Returns the watchlist.
    const Repository& getWatchlist();
};


