#pragma once


#include "repository.h"

class FileRepository: public Repository{
private:
    std::string filename;

    void read();

    void write();

public:

    FileRepository();

    explicit FileRepository(const std::string& filename);

    ~FileRepository() override;

    void addElement(const TElem& element) override;

    void deleteElement(int position) override;

    void updateElement(int position, int newLikes) override;

};
