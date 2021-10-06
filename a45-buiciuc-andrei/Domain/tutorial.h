#pragma once
#include <utility>
#include <string>

class Tutorial {
    private:
        std::string title;
        std::string presenter;
        std::pair<int, int> duration;
        int likes;
        std::string link;

    public:

    /// Constructor
    Tutorial();

    /// Constructor
    /// \param title: Title of the tutorial
    /// \param presenter: Presenter of the tutorial
    /// \param likes: The number of likes
    /// \param link: The link to the tutorial
    Tutorial(std::string title, std::string presenter, std::pair<int, int>, int likes, std::string link);

    /// Returns the title of the tutorial
    std::string get_title();

    /// Return the presenter of the tutorial
    std::string get_presenter();

    /// Returns the duration of the tutorial
    std::pair<int, int> get_duration();

    /// Returns the number of likes of the tutorial
    int get_likes();

    /// Returns the link to the tutorial
    std::string get_link();

    /// Sets the number of likes for a tutorial
    void set_likes(int likes);

    /// Converts a tutorial to a string containing its information
    std::string str();
};