#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>

class Tutorial {
    private:
        std::string title;
        std::string presenter;
        std::pair<int, int> duration;
        int likes{};
        std::string link;

    public:

    /// Constructor
    Tutorial();

    /// Constructor
    Tutorial(const std::string& title, const std::string& presenter, std::pair<int, int>, int likes,
             const std::string& link);

    /// Copy constructor
    Tutorial(const Tutorial& t);

    const std::string& getTitle() const;

    void setTitle(const std::string& value);

    const std::string& getPresenter() const;

    void setPresenter(const std::string& value);

    std::pair<int, int> getDuration() const;

    void setDuration(std::pair<int, int>value);

    int getLikes() const;

    void setLikes(int value);

    std::string getLink() const;

    void setLink(const std::string& value);

    /// Converts a tutorial to a string containing its information
    std::string str() const;

    /// Tokenizes a line representing a tutorial
    friend void tokenize(const std::string& line, std::vector<std::string>& tokens, char delimiter);

    /// Operator << overload
    friend std::ostream &operator<<(std::ostream &output, const Tutorial& tutorial);

    /// Operator >> overload
    friend std::istream &operator>>(std::istream &input, Tutorial& tutorial);
};