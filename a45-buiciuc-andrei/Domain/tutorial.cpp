#include "tutorial.h"
using namespace std;

Tutorial::Tutorial() {}

Tutorial::Tutorial(string title, string presenter, pair<int, int> duration, int likes, string link) {
    this->title = title;
    this->presenter = presenter;
    this->duration = duration;
    this->likes = likes;
    this->link = link;
}

string Tutorial::get_title()  { return this->title; }


string Tutorial::get_presenter() { return this->presenter; }


pair<int, int> Tutorial::get_duration() { return this->duration; }


int Tutorial::get_likes() { return this->likes; }


string Tutorial::get_link() { return this->link; }


void Tutorial::set_likes(int likes) { this->likes = likes; }


string Tutorial::str() {
    string tutorial_str = "";
    tutorial_str += this->title + " | " + this->presenter + " | " + to_string(this->duration.first) + ":" +
            to_string(this->duration.second) + " | " + to_string(this->likes) + " | " + this->link;
    return tutorial_str;
}