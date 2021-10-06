#include "controller.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "undo_controller.h"

Controller* create_controller(int repo_capacity){
    Controller* controller = (Controller*)malloc(sizeof(Controller));
    if(controller == NULL){
        return NULL;
    }

    controller->repository = create_repository(repo_capacity);

    return controller;
}

void destroy_controller(Controller* controller){
    // Free the repository.
    destroy_repository(controller->repository);
    // Free the controller.
    free(controller);
}

Repository* get_repo(Controller* controller){
    return controller->repository;
}

int find_material(Controller* controller, char name[], char supplier[], Date expiration_date){
    Dynamic_Array material_list = get_data(controller->repository);
    int position = -1;
    for(int i = 0; i < material_list.length; i++){
        Material material = material_list.elements[i];
        if(strcmp(material.name, name) == 0 &&
           strcmp(material.supplier, supplier) == 0 &&
           material.expiration_date.year == expiration_date.year &&
           material.expiration_date.month == expiration_date.month &&
           material.expiration_date.day == expiration_date.day)
        {
            position = i;
            break;
        }
    }

    return position;
}

void add_element(Controller* controller, char name[], char supplier[], int quantity, Date expiration_date){
    Material new_material = create_material(name, supplier, quantity, expiration_date);

    int position = find_material(controller, new_material.name, new_material.supplier, new_material.expiration_date);
    Material old_material = get_data(controller->repository).elements[position];

    if(position == -1) {
        add_material(controller->repository, new_material);
    }
    else {
        set_quantity(&get_data(controller->repository).elements[position], new_material.quantity + old_material.quantity);
    }

}

int delete_element(Controller* controller, char name[], char supplier[], Date expiration_date){
    int position = find_material(controller, name, supplier, expiration_date);
    if(position == -1){
        return -1;
    }
    else {
        delete_material(controller->repository, position);
        return 1;
    }
}

int update_element(Controller* controller, char name[], char supplier[], Date expiration_date, int new_quantity){
    int position = find_material(controller, name, supplier, expiration_date);
    if(position == -1){
        return -1;
    }
    else{
        update_material(controller->repository, position, new_quantity);
        return 1;
    }
}

int compare_elements_name(const void* material_1, const void* material_2){
    return strcmp(((Material*)material_1)->name, ((Material*)material_2)->name);
}

int compare_elements_supplier(const void* material_1, const void* material_2){
    return strcmp(((Material*)material_1)->supplier, ((Material*)material_2)->supplier);
}

int compare_elements_quantity(const void* material_1, const void* material_2){
    return ((Material*)material_1)->quantity > ((Material*)material_2)->quantity;
}

int compare_elements_quantity_descending(const void* material_1, const void* material_2){
    return ((Material*)material_1)->quantity < ((Material*)material_2)->quantity;

}

void sort_elements_options(Material materials_data[], int array_length, char option[]){
    if(strcmp(option, "name") == 0)
        qsort(materials_data, (size_t) array_length, sizeof(Material), compare_elements_name);
    else if(strcmp(option, "supplier") == 0)
        qsort(materials_data, (size_t) array_length, sizeof(Material), compare_elements_supplier);
    else if(strcmp(option, "ascending") == 0)
        qsort(materials_data, (size_t) array_length, sizeof(Material), compare_elements_quantity);
    else if(strcmp(option, "descending") == 0)
        qsort(materials_data, (size_t) array_length, sizeof(Material), compare_elements_quantity_descending);
}

int elements_past_expiration(Controller* controller, Material materials_data[], char substring[]){
    // With this header: #include <time.h>
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;

    int array_length = 0;
    Dynamic_Array material_list = get_repo(controller)->material_list;
    Material material;
    for(int i = 0; i < material_list.length; i ++){
        material = material_list.elements[i];
        if(strstr(material.name, substring) != NULL || strstr(material.supplier, substring) != NULL || strstr(substring, "...")) {
            if (material.expiration_date.year < year) {
                materials_data[array_length] = material;
                array_length += 1;
            } else if (material.expiration_date.year == year && material.expiration_date.month < month) {
                materials_data[array_length] = material;
                array_length += 1;
            } else if (material.expiration_date.year == year && material.expiration_date.month == month &&
                       material.expiration_date.day < day) {
                materials_data[array_length] = material;
                array_length += 1;
            }
        }
    }
    return array_length;
}

int elements_from_a_supplier(Controller* controller, Material* materials_data, char supplier[]){
    int array_length = 0;
    Dynamic_Array material_list = get_repo(controller)->material_list;
    Material material;
    for(int i = 0; i < material_list.length; i ++){
        material = material_list.elements[i];
        if(strcmp(material.supplier, supplier) == 0){
            materials_data[array_length] = material;
            array_length += 1;
        }
    }
    return array_length;
}

int elements_short_on_supply(Controller* controller, Material material_data[], int supply){
    int array_length = 0;
    Dynamic_Array material_list = get_repo(controller)->material_list;
    Material material;
    for(int i = 0; i < material_list.length; i ++){
        material = material_list.elements[i];
        if(material.quantity < supply){
            material_data[array_length] = material;
            array_length ++;
        }
    }

    return array_length;
}