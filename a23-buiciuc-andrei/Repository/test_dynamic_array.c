#include "test_dynamic_array.h"
#include "repository.h"
#include <assert.h>



void test_dynamic_array(){
    // Dynamic_Array* array = create_dynamic_array(2);
    Repository* repo = create_repository(2);
    if(&repo->material_list == NULL){
        assert(0);
    }

    assert(repo->material_list.capacity == 2);
    assert(repo->material_list.length == 0);

    Material m1 = create_material("water", "aqua", 100, create_expiration_date(2001, 4, 4));
    add_material(repo, m1);
    assert(repo->material_list.length == 1);

    Material m2 = create_material("salt", "mine", 400, create_expiration_date(2002, 5, 6));
    add_material(repo, m2);
    assert(repo->material_list.length == 2);

    // Capacity must double
    Material m3 = create_material("sugar", "sugar_cane", 300, create_expiration_date(2004,4,8));
    add_material(repo, m3);
    assert(repo->material_list.length == 3);
    assert(repo->material_list.capacity == 4);

    destroy_repository(repo);
}