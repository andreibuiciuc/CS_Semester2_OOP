#include "repository.h"
#include "../Domain/tutorial.h"

Repository::Repository(DynamicArray<Tutorial>* data) {this->data = data; }

Repository::~Repository() {}

void Repository::addElement(Tutorial element) { this->data->addElement(element); }

void Repository::deleteElement(int position) { this->data->deleteElement(position); }

void Repository::updateElement(int position, int new_likes) { this->data->updateElement(position, new_likes); }

DynamicArray<Tutorial>* Repository::getArray() const {return this->data; }

void Repository::initRepository() {
    std::pair<int,int>p1(40,26);
    Tutorial t1 = Tutorial("C++ Programming", "Mike Dane", p1, 70, "https://www.youtube.com/watch?v=raZSmcariyU");

    std::pair<int,int>p2(16,58);
    Tutorial t2 = Tutorial("POINTERS in C++", "The Cherno", p2, 489, "https://www.youtube.com/watch?v=DTxHyVn0ODg");

    std::pair<int,int>p3(19,30);
    Tutorial t3 = Tutorial("Stack vs Heap Memory in C++", "The Cherno", p3, 252, "https://www.youtube.com/watch?v=wJ1L2nSIV1s");

    std::pair<int,int>p4(22,51);
    Tutorial t4 = Tutorial("C++ Tutorial 2020", "Derek Banas", p4, 168, "https://www.youtube.com/watch?v=6y0bp-mnYU0");

    std::pair<int,int>p5(7,33);
    Tutorial t5 = Tutorial("OOP in 7 minutes", "Mosh", p5, 1869, "https://www.youtube.com/watch?v=pTB0EiLXUC8");

    std::pair<int,int>p6(41,54);
    Tutorial t6 = Tutorial("What Are Pointers? (C++)", "javidx9", p6, 370, "https://www.youtube.com/watch?v=iChalAKXffs");

    std::pair<int,int>p7(58,17);
    Tutorial t7 = Tutorial("Networking in C++", "javidx9", p7, 233, "https://www.youtube.com/watch?v=2hNdkYInj4g");

    std::pair<int,int>p8(8,44);
    Tutorial t8 = Tutorial("Inheritance in OOP C++", "Apna College", p8, 20, "https://www.youtube.com/watch?v=7ZfEp71tIec");

    std::pair<int,int>p9(10,8);
    Tutorial t9 = Tutorial("Polymorphism in C++", "Apna College", p9, 23, "https://www.youtube.com/watch?v=F5PbnZkHqmg");

    std::pair<int,int>p10(5,45);
    Tutorial t10 = Tutorial("A Tour of Modern C++", "JetBrainsTV", p10, 118, "https://www.youtube.com/watch?v=iWvcoIKSaoc");

    this->addElement(t1);
    this->addElement(t2);
    this->addElement(t3);
    this->addElement(t4);
    this->addElement(t5);
    this->addElement(t6);
    this->addElement(t7);
    this->addElement(t8);
    this->addElement(t9);
    this->addElement(t10);
}

