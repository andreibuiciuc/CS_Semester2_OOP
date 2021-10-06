#pragma once
#include "../Repository/repository.h"
#include "../Domain/tutorial.h"

class Controller{
    private:
        Repository* repository;
        DynamicArray<Tutorial>* watchlist;

    public:

    /// Constructor
    /// \param repository: pointer to the repository
    Controller(Repository* repository, DynamicArray<Tutorial>* watchlist);

    /// Destructor
    ~Controller();

    /// Returns a pointer to the repository
    Repository* getRepo();

    /// Find the index position of an element.
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: the index position of the element, -1 otherwise
    int findElement(std::string title, std::string presenter);

    /// Adds an element
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \param duration: a given duration
    /// \param likes: a given number of likes
    /// \param link: a given link
    /// \return: 0 for success, 1 for failure
    int addElement(std::string title, std::string presenter, std::pair<int,int>duration, int likes, std::string link);

    /// Deletes an element
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: 0 for success, 1 for failure
    int deleteElement(std::string title, std::string presenter);

    /// Updates an element
    /// \param title: a given title
    /// \param presenter: a given presenter
    /// \return: 0 for success, 1 for failure
    int updateElement(std::string title, std::string presenter, int new_likes);

        /// Filters the array of tutorials by the presenter
        /// \param presenter: a given presenter
        /// \return: the length of the new array
        int filterTutorialsByPresenter(DynamicArray<Tutorial>* filteredTutorials, std::string presenter);

        /// Finds a tutorial in the watchlist.
        /// \param title: a given title
        /// \param presenter: a given presenter
        /// \return: the position in the watchlist, -1 otherwise
        int findTutorialInWatchlist(std::string title, std::string presenter);

        /// Adds a tutorial to the watchlist
        /// \param tutorial: a given tutorial
        /// \return: 0 if added, 1 if tutorial already in the watchlist
        int addToWatchlist(Tutorial tutorial);

        /// Deletes a tutorial from the watchlist
        /// \param title: a given title
        /// \param presenter: a given presenter
        /// \return: 0 if deleted, 1 if tutorial not in the watchlist
        int deleteTutorialFromWatchlist(std::string title, std::string presenter);

        /// Returns the watchlist.
        DynamicArray<Tutorial>* getWatchlist();
};