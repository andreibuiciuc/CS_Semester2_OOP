#include "test_controller.h"
#include "controller.h"
#include <assert.h>
#include <stdlib.h>

void test_create_destroy_controller(){
    Controller* controller = create_controller(5);
    assert(controller != NULL);
    assert(controller->repository->material_list.capacity == 5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.elements != NULL);
    destroy_controller(controller);
}


void test_add_element(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2002, 2, 2));
    assert(controller->repository->material_list.length == 2);

    add_element(controller, "material1", "supp1", 1000, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 2);
    assert(controller->repository->material_list.elements[0].quantity == 1100);

    destroy_controller(controller);
}


void test_delete_element(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2002, 2, 2));
    assert(controller->repository->material_list.length == 2);

    add_element(controller, "material1", "supp1", 1000, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 2);
    assert(controller->repository->material_list.elements[0].quantity == 1100);

    int x;
    x = delete_element(controller, "material1", "supp1", create_expiration_date(2001, 1, 1));
    assert(x == 1);
    assert(controller->repository->material_list.length == 1);

    x = delete_element(controller, "material1", "supp1", create_expiration_date(2001, 1, 1));
    assert(x == -1);

    destroy_controller(controller);
}


void test_update_element(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2002, 2, 2));
    assert(controller->repository->material_list.length == 2);

    add_element(controller, "material1", "supp1", 1000, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 2);
    assert(controller->repository->material_list.elements[0].quantity == 1100);

    int x;
    x = update_element(controller, "material1", "supp1", create_expiration_date(2001, 1, 1), 1000);
    assert(x == 1);
    assert(controller->repository->material_list.elements[0].quantity == 1000);

    x = delete_element(controller, "material1", "supp1", create_expiration_date(2001, 1, 1));
    assert(x == 1);
    assert(controller->repository->material_list.length == 1);

    x = update_element(controller, "material1", "supp1", create_expiration_date(2001, 1, 1), 1000);
    assert(x == -1);

    destroy_controller(controller);
}


void test_find_material(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2002, 2, 2));
    assert(controller->repository->material_list.length == 2);

    add_element(controller, "material1", "supp1", 1000, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 2);
    assert(controller->repository->material_list.elements[0].quantity == 1100);

    int x;
    x = find_material(controller, "material1", "supp1", create_expiration_date(2001, 1, 1));
    assert(x == 0);

    x = find_material(controller, "material2", "supp1", create_expiration_date(2001, 1, 1));
    assert(x == -1);

    destroy_controller(controller);
}


void test_get_repo(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2002, 2, 2));
    assert(controller->repository->material_list.length == 2);

    add_element(controller, "material1", "supp1", 1000, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 2);
    assert(controller->repository->material_list.elements[0].quantity == 1100);

    Repository* repo = get_repo(controller);
    assert(repo->material_list.length == 2);
    assert(repo->material_list.capacity == 5);
    assert(repo->material_list.elements != NULL);

    destroy_controller(controller);
}


void test_sorts(){
    Material* data = (Material*)malloc(2*sizeof(Material));
    Material m1 = create_material("a", "zupp1", 100, create_expiration_date(2001, 1, 1));
    Material m2 = create_material("b", "supp1", 200, create_expiration_date(2001, 3, 4));
    data[0] = m1;
    data[1] = m2;

    sort_elements_options(data, 2, "name");
    assert(data[0].quantity == 100);
    assert(data[1].quantity == 200);

    sort_elements_options(data, 2, "supplier");
    assert(data[0].quantity == 200);
    assert(data[1].quantity == 100);

    free(data);
}


void test_past_expiration_date(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2022, 2, 2));
    assert(controller->repository->material_list.length == 2);

    Material* data = (Material*)malloc(2 * sizeof(Material));
    int x;
    x = elements_past_expiration(controller, data, "up");
    assert(x == 1);
    assert(data[0].quantity == 100);

    free(data);
    destroy_controller(controller);
}

void test_short_on_supply(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2022, 2, 2));
    assert(controller->repository->material_list.length == 2);

    Material* data = (Material*)malloc(2 * sizeof(Material));
    int x;
    x = elements_short_on_supply(controller, data, 500);
    assert(x == 2);
    assert(data[0].quantity == 100);
    assert(data[1].quantity == 200);

    free(data);
    destroy_controller(controller);
}


void test_from_supplier(){
    Controller* controller = create_controller(5);
    assert(controller->repository->material_list.length == 0);
    assert(controller->repository->material_list.capacity == 5);

    add_element(controller, "material1", "supp1", 100, create_expiration_date(2001, 1, 1));
    assert(controller->repository->material_list.length == 1);

    add_element(controller, "material2", "supp2", 200, create_expiration_date(2022, 2, 2));
    assert(controller->repository->material_list.length == 2);

    Material* data = (Material*)malloc(2 * sizeof(Material));
    int x;
    x = elements_from_a_supplier(controller, data, "supp2");
    assert(x == 1);
    assert(data[0].quantity == 200);

    free(data);
    destroy_controller(controller);

}

void test_controller(){
    test_create_destroy_controller();
    test_add_element();
    test_delete_element();
    test_update_element();
    test_find_material();
    test_get_repo();
    test_sorts();
    test_past_expiration_date();
    test_from_supplier();
    test_short_on_supply();
}