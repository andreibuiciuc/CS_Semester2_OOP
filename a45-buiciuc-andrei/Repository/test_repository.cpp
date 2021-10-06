#include "test_repository.h"
#include "dynamicArray.h"
#include "repository.h"
#include "../Domain/tutorial.h"
#include <assert.h>

void test_repository(){
    DynamicArray<Tutorial>* data = new DynamicArray<Tutorial>(4);
    Repository* repository = new Repository(data);
    std::pair<int, int> p1(20,30);
    Tutorial t1("C++ Essentials", "Bui", p1, 1000, "asdsad");

    assert(repository->getArray()->getLength() == 0);
    repository->addElement(t1);
    assert(repository->getArray()->getLength() == 1);
    repository->deleteElement(0);
    assert(repository->getArray()->getLength() == 0);
    repository->addElement(t1);
    repository->updateElement(0, 1500);
    assert(repository->getArray()->getData()[0].get_likes() == 1500);

    delete data;
    delete repository;
}
