#include "test_material.h"
#include "material.h"
#include "assert.h"
#include <string.h>
#include <stdio.h>

void test_create_expiration_date(){
    Date date1 = create_expiration_date(2021, 5, 5);
    assert(date1.year == 2021);
    assert(date1.month == 5);
    assert(date1.day == 5);

    Date date2 = create_expiration_date(2000, 2, 2);
    assert(date2.year == 2000);
    assert(date2.month == 2);
    assert(date2.day == 2);
}

void test_create_material(){
    Material m1 = create_material("material", "supp", 100, create_expiration_date(2000, 2, 2));
    assert(strcmp(m1.name, "material") == 0);
    assert(strcmp(m1.supplier, "supp") == 0);
    assert(m1.quantity == 100);
    assert(m1.expiration_date.year == 2000);
    assert(m1.expiration_date.month == 2);
    assert(m1.expiration_date.day == 2);
}

void test_set_quantity(){
    Material m1 = create_material("material", "supp", 100, create_expiration_date(2000, 2, 2));
    assert(m1.quantity == 100);
    set_quantity(&m1, 500);
    assert(m1.quantity == 500);
    set_quantity(&m1,1000);
    assert(m1.quantity == 1000);
    set_quantity(&m1, 0);
    assert(m1.quantity == 0);
}

void test_to_str(){
    Material m1 = create_material("material", "supp", 100, create_expiration_date(2000, 2, 2));
    char str[50];
    to_str(m1, str);
    assert(strcmp(str, "material - supp - 100 - 2:2:2000") == 0);

    Material m2 = create_material("a", "a", 1000, create_expiration_date(1990, 12, 12));
    char str2[50];
    to_str(m2, str2);
    assert(strcmp(str2, "a - a - 1000 - 12:12:1990") == 0);


}

void test_domain(){
    test_create_expiration_date();
    test_create_material();
    test_set_quantity();
    test_to_str();
}