#include <fstream>
#include "AbstractWatchlist.h"

AbstractWatchlist::AbstractWatchlist() = default;

AbstractWatchlist::~AbstractWatchlist() = default;

void AbstractWatchlist::setData(const std::vector<Tutorial>& value) {
    this->data = value;
}

void AbstractWatchlist::process(const std::vector<Tutorial>& tutorials) {
    this->setData(tutorials);
    this->write();
    this->open();
}

CSVWatchlist::CSVWatchlist(const std::string &filename){
    this->filename = filename;
}

CSVWatchlist::~CSVWatchlist() = default;

void CSVWatchlist::open() {
    ShellExecute(nullptr, "open", this->filename.c_str(), nullptr, nullptr, SW_SHOW);
}

void CSVWatchlist::write() {
    std::fstream file;
    file.open(this->filename, std::ios::out);
    if(file.is_open()) {
        for(const auto& element: this->data) {
            file << element << '\n';
        }
    }
    file.close();
}

HTMLWatchlist::HTMLWatchlist(const std::string &filename){
    this->filename = filename;
}

HTMLWatchlist::~HTMLWatchlist() = default;

void HTMLWatchlist::open() {
    ShellExecute(nullptr, "open", this->filename.c_str(), nullptr, nullptr, SW_SHOW);
}

void HTMLWatchlist::write() {
    std::fstream file;
    file.open(this->filename, std::ios::out);
    if(file.is_open()) {
        file << "<DOCTYPE html>\n";
        file << "<html>\n";
        file << "<head>\n";
        file << "\t<title> Watchlist </title>\n";
        file << "</head>\n";
        file << "<body>\n";
        file << "<table border=\"1\">\n";
        file << "\t<tr>\n";
        file << "\t\t<td> Title </td>\n";
        file << "\t\t<td> Presenter </td>\n";
        file << "\t\t<td> Minutes </td>\n";
        file << "\t\t<td> Seconds </td>\n";
        file << "\t\t<td> Likes </td>\n";
        file << "\t\t<td> Link </td>\n";
        file << "</tr>\n";

        for (const auto &tutorial: this->data) {
            file << "\t<tr>\n";
            file << "\t\t<td>" << tutorial.getTitle() << " </td>\n";
            file << "\t\t<td>" << tutorial.getPresenter() << "</td>\n";
            file << "\t\t<td>" << tutorial.getDuration().first << " </td>\n";
            file << "\t\t<td>" << tutorial.getDuration().second << " </td>\n";
            file << "\t\t<td>" << tutorial.getLikes() << " </td>\n";
            file << "\t\t<td>" << tutorial.getLink() << " </td>\n";
            file << "</tr>\n";
        }

        file << "</table>\n";
        file << "</body>\n";
        file << "</html>\n";
    }
    else
        return;

    file.close();
    this->data.clear();
}
