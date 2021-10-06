#include "test_dynamic_array.h"
#include "dynamicArray.h"
#include "../Domain/tutorial.h"
#include "assert.h"

void test_dynamic_array(){
    DynamicArray<Tutorial>* array = new DynamicArray<Tutorial>(2);
    assert(array->getCapacity() == 2);
    assert(array->getLength() == 0);

    std::pair<int, int> p1(20,30);
    Tutorial t1("C++", "Bui", p1, 1000, "sadsd");
    array->addElement(t1);
    assert(array->getLength() == 1);
    assert(array->getCapacity() == 2);

    std::pair<int, int> p2(21,31);
    Tutorial t2("C#", "John", p2, 500, "sasd");
    array->addElement(t2);
    assert(array->getLength() == 2);
    assert(array->getCapacity() == 2);

    std::pair<int, int> p3(22,32);
    Tutorial t3("Python 101", "Snake", p3, 1200, "sdasd");
    array->addElement(t3);
    assert(array->getLength() == 3);
    assert(array->getCapacity() == 4);

    array->deleteElement(0);
    assert(array->getLength() == 2);

    array->updateElement(1, 2000);
    assert(array->getData()[1].get_likes() == 2000);


    delete array;

}