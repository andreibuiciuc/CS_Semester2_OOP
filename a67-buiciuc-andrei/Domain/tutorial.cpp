#include <sstream>
#include "tutorial.h"

Tutorial::Tutorial() = default;

Tutorial::Tutorial(const std::string& title, const std::string& presenter, std::pair<int, int> duration, int likes,
                   const std::string& link) {
    this->title = title;
    this->presenter = presenter;
    this->duration = duration;
    this->likes = likes;
    this->link = link;
}

Tutorial::Tutorial(const Tutorial &t) {
    this->title = t.title;
    this->presenter = t.presenter;
    this->duration = t.duration;
    this->likes = t.likes;
    this->link = t.link;
}

const std::string& Tutorial::getTitle() const { return this->title; }

void Tutorial::setTitle(const std::string& value) { this->title = value; }

const std::string& Tutorial::getPresenter() const { return this->presenter; }

void Tutorial::setPresenter(const std::string &value) { this->presenter = value; }

std::pair<int, int> Tutorial::getDuration() const { return this->duration; }

void Tutorial::setDuration(std::pair<int, int> value) { this->duration = value; }

int Tutorial::getLikes() const { return this->likes; }

void Tutorial::setLikes(int value) { this->likes = value; }

std::string Tutorial::getLink() const { return this->link; }

void Tutorial::setLink(const std::string &value) { this->link = value; }

std::string Tutorial::str() const {
    std::string tutorial_str;
    tutorial_str += this->title + " | " + this->presenter + " | " + std::to_string(this->duration.first) + ":" +
            std::to_string(this->duration.second) + " | " + std::to_string(this->likes) + " | " + this->link;
    return tutorial_str;
}

void tokenize(const std::string& line, std::vector<std::string>& tokens, char delimiter) {
    std::stringstream ss(line);
    std::string token;
    while(std::getline(ss, token, delimiter))
        tokens.push_back(token);
}

std::ostream &operator<<(std::ostream &output, const Tutorial& tutorial) {
    output << tutorial.title << "," << tutorial.presenter << "," << tutorial.duration.first << ","
           << tutorial.duration.second << "," << tutorial.likes << "," << tutorial.link;
    return output;
}

std::istream &operator>>(std::istream &input, Tutorial& tutorial) {
    std::string line;
    std::getline(input, line);
    std::vector<std::string> tokens;
    tokenize(line, tokens, ',');
    if(tokens.size() != 6) {
        return input;
    }

    tutorial.setTitle(tokens[0]);
    tutorial.setPresenter(tokens[1]);
    int minutes = stoi(tokens[2]);
    int seconds = stoi(tokens[3]);
    std::pair<int,int>p(minutes, seconds);
    tutorial.setDuration(p);
    int likes = stoi(tokens[4]);
    tutorial.setLikes(likes);
    tutorial.setLink(tokens[5]);

    return input;
}
