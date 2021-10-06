#include "fileRepository.h"
#include <fstream>
#include <sstream>

FileRepository::FileRepository() = default;

FileRepository::FileRepository(const std::string& filename): Repository{} {
    this->filename = filename;
    this->read();
}

FileRepository::~FileRepository() = default;

void FileRepository::addElement(const TElem &element) {
    Repository::addElement(element);
    this->write();
}

void FileRepository::deleteElement(int position) {
    Repository::deleteElement(position);
    this->write();
}

void FileRepository::updateElement(int position, int newLikes) {
    Repository::updateElement(position, newLikes);
    this->write();
}

void FileRepository::read() {
    std::fstream file;
    file.open(this->filename);
    Tutorial tutorial;

    if(!file.is_open()) {
        return;
    }
    while(file >> tutorial) {
        Repository::addElement(tutorial);
    }

    file.close();
}

void FileRepository::write() {
    std::fstream file;
    file.open(this->filename, std::ios::out);
    if(file.is_open()) {
        for(const auto& element: this->data) {
            file << element << '\n';
        }
    }
    else
        return;

    file.close();
}
