#include "test_init.h"

void test_init(Repository* repository){
    Material m1 = create_material("Sugar", "SugarLand", 100, create_expiration_date(2030, 3, 15));
    add_material(repository, m1);
    Material m2 = create_material("Milk", "Cows.Co", 200, create_expiration_date(2001, 3, 20));
    add_material(repository, m2);
    Material m3 = create_material("Milk", "Other-Cows.Co", 150, create_expiration_date(2021, 3, 22));
    add_material(repository, m3);
    Material m4 = create_material("Flour", "BigMill", 500, create_expiration_date(2027, 4, 5));
    add_material(repository, m4);
    Material m5 = create_material("Salt", "UnderMine", 150, create_expiration_date(2004, 1, 1));
    add_material(repository, m5);
    Material m6 = create_material("Water", "Aqua.Co", 500,create_expiration_date(2040, 2, 4));
    add_material(repository, m6);
    Material m7 = create_material("Chocolate", "Wilka", 300, create_expiration_date(2019, 6, 6));
    add_material(repository, m7);
    Material m8 = create_material("Vanilla", "Wilka", 400, create_expiration_date(2020, 1, 1));
    add_material(repository, m8);
    Material m9 = create_material("Caramel", "WillyWonka", 250, create_expiration_date(2021, 5, 3));
    add_material(repository, m9);
    Material m10 = create_material("Seeds", "Store", 100, create_expiration_date(2022, 6, 24));
    add_material(repository, m10);
}
