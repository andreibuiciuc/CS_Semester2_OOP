#include <algorithm>
#include "controllerUser.h"
#include "../Exception/customException.h"

ControllerUser::ControllerUser() = default;

ControllerUser::ControllerUser(const Repository &repository, const Repository &watchlist) {
    this->repository = repository;
    this->watchlist = watchlist;
}

ControllerUser::ControllerUser(const ControllerUser &controllerUser) {
    this->repository = controllerUser.repository;
    this->watchlist = controllerUser.watchlist;
}

ControllerUser::~ControllerUser() = default;

void ControllerUser::filterTutorialsByPresenter(std::vector<Tutorial>& filteredTutorials, const std::string& presenter) {
    std::vector<Tutorial> data = this->repository.getData();

    if(presenter.empty()) {
        // The case when the user provides an empty string.
        for(const auto& tutorial: this->repository.getData())
            filteredTutorials.push_back(tutorial);

    }
    else {
        // The case when the user provides a presenter name.
        filteredTutorials.resize(data.size());
        auto it = std::copy_if(data.begin(), data.end(), filteredTutorials.begin(),
                     [&presenter](const Tutorial& tutorial) { return tutorial.getPresenter() == presenter; });
        filteredTutorials.resize(std::distance(filteredTutorials.begin(), it));
    }
}

int ControllerUser::findTutorialInWatchlist(const std::string& title, const std::string& presenter) {
    int index = 0;
    for(const auto& element: this->watchlist.getData()) {
        if(element.getTitle() == title && element.getPresenter() == presenter) {
            break;
        }
        index ++;
    }

    if(index == this->watchlist.getLength()) {
        return -1;
    }
    return index;
}

void ControllerUser::addToWatchlist(const Tutorial& tutorial) {
    int index = this->findTutorialInWatchlist(tutorial.getTitle(), tutorial.getPresenter());
    if(index == -1) {
        this->watchlist.addElement(tutorial);
    }
    else {
        throw ControllerException("Tutorial already in the watchlist.");
    }
}

void ControllerUser::deleteTutorialFromWatchlist(const std::string& title, const std::string& presenter) {
    int index = this->findTutorialInWatchlist(title, presenter);
    if(index == -1) {
        throw ControllerException("Tutorial not in the watchlist.");
    }
    else {
        this->watchlist.deleteElement(index);
    }
}

const Repository& ControllerUser::getWatchlist() { return this->watchlist; }
