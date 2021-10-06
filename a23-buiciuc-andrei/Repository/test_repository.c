#include "test_repository.h"
#include "repository.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_create_destroy_repository(){
    Repository* repo = create_repository(2);
    assert(repo != NULL);
    assert(repo->material_list.length == 0);
    assert(repo->material_list.capacity == 2);
    assert(repo->material_list.elements != NULL);
    destroy_repository(repo);
}


void test_resize(){
    Repository* repo = create_repository(2);
    resize(repo);
    assert(repo->material_list.capacity == 4);
    destroy_repository(repo);
}


void test_add_material(){
    Repository* repo = create_repository(5);

    assert(repo->material_list.length == 0);

    Material m1 = create_material("material", "supp", 100, create_expiration_date(2000,2,2));
    add_material(repo, m1);
    assert(repo->material_list.length == 1);
    assert(strcmp(repo->material_list.elements[0].name, "material") == 0);

    Material m2 = create_material("material2", "supp2", 200, create_expiration_date(2004,4,4));
    add_material(repo, m2);
    assert(repo->material_list.length == 2);

    destroy_repository(repo);
}


void test_delete_material(){
    Repository* repo = create_repository(5);

    assert(repo->material_list.length == 0);

    Material m1 = create_material("material", "supp", 100, create_expiration_date(2001,1,1));
    add_material(repo, m1);
    assert(repo->material_list.length == 1);
    assert(strcmp(repo->material_list.elements[0].name, "material") == 0);

    Material m2 = create_material("material2", "supp2", 200, create_expiration_date(2002,2,2));
    add_material(repo, m2);
    assert(repo->material_list.length == 2);

    Material m3 = create_material("material3", "supp3", 300, create_expiration_date(2003, 3,3));
    add_material(repo, m3);
    assert(repo->material_list.length == 3);

    delete_material(repo, 1);
    assert(repo->material_list.length == 2);

    delete_material(repo, 0);
    assert(repo->material_list.length == 1);

    destroy_repository(repo);
}


void test_update_material(){
    Repository* repo = create_repository(5);

    assert(repo->material_list.length == 0);

    Material m1 = create_material("material", "supp", 100, create_expiration_date(2001,1,1));
    add_material(repo, m1);
    assert(repo->material_list.length == 1);
    assert(strcmp(repo->material_list.elements[0].name, "material") == 0);

    Material m2 = create_material("material2", "supp2", 200, create_expiration_date(2002,2,2));
    add_material(repo, m2);
    assert(repo->material_list.length == 2);

    Material m3 = create_material("material3", "supp3", 300, create_expiration_date(2003, 3,3));
    add_material(repo, m3);
    assert(repo->material_list.length == 3);

    update_material(repo, 0, 1000);
    assert(repo->material_list.elements[0].quantity == 1000);

    update_material(repo, 2, 3000);
    assert(repo->material_list.elements[2].quantity == 3000);

    destroy_repository(repo);
}


void test_get_data(){
    Repository* repo = create_repository(5);

    assert(repo->material_list.length == 0);

    Material m1 = create_material("material", "supp", 100, create_expiration_date(2001,1,1));
    add_material(repo, m1);
    assert(repo->material_list.length == 1);
    assert(strcmp(repo->material_list.elements[0].name, "material") == 0);

    Material m2 = create_material("material2", "supp2", 200, create_expiration_date(2002,2,2));
    add_material(repo, m2);
    assert(repo->material_list.length == 2);

    Dynamic_Array data = get_data(repo);
    assert(data.length == 2);
    assert(data.capacity == 5);

    destroy_repository(repo);
}


void test_load_new_container(){
    Repository* repo = create_repository(1);

    assert(repo->material_list.length == 0);

    Material m1 = create_material("material", "supp", 100, create_expiration_date(2001,1,1));
    add_material(repo, m1);
    assert(repo->material_list.length == 1);
    assert(strcmp(repo->material_list.elements[0].name, "material") == 0);

    Dynamic_Array* container = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
    container->capacity = 5;
    container->length = 0;

    container->elements = (Material*)malloc(container->capacity* sizeof(Material));

    container->elements[container->length] = m1;
    container->length += 1;
    container->elements[container->length] = m1;
    container->length += 1;

    load_new_container(repo, container);
    assert(repo->material_list.length == 2);
    assert(repo->material_list.capacity == 5);

    free(container->elements);
    free(container);
    destroy_repository(repo);
}


void test_repository(){
    test_create_destroy_repository();
    test_resize();
    test_add_material();
    test_delete_material();
    test_update_material();
    test_get_data();
    test_load_new_container();
}

