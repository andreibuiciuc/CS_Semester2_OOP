#include "repository.h"
#include <stdlib.h>

Repository* create_repository(int repo_capacity){
    Repository* repo = (Repository*)malloc(sizeof(Repository));

    if(repo == NULL){
        return NULL;
    }

    repo->material_list = create_dynamic_array(repo_capacity);
    // repo->material_list.elements = (Material*)malloc(repo_capacity * sizeof(Material));

    if(repo->material_list.elements == NULL){
        return NULL;
    }

//    repo->material_list.capacity = repo_capacity;
//    repo->material_list.length = 0;

    return repo;
}

void destroy_repository(Repository* repo){
    // Free the dynamic array.
    if (repo == NULL)
        return;
    destroy_dynamic_array(&repo->material_list);
    free(repo);
}

void resize(Repository* repo){
//    repo->material_list.capacity = repo->material_list.capacity * 2;
//    Material* new_array = (Material*)malloc(repo->material_list.capacity * sizeof(Material));
//
//    for(int i=0; i <repo->material_list.length; i++){
//        new_array[i] = repo->material_list.elements[i];
//    }
//
//    free(repo->material_list.elements);
//    repo->material_list.elements = new_array;

    resize_dynamic_array(&repo->material_list);
}

Dynamic_Array get_data(Repository* repo){
    return repo->material_list;
}

void add_material(Repository* repo, Material element){

//    if(&repo->material_list == NULL){
//        return;
//    }
//    if(repo->material_list.elements == NULL){
//        return;
//    }
//    if(repo->material_list.length == repo->material_list.capacity){
//        resize(repo);
//    }
//
//    repo->material_list.elements[repo->material_list.length] = element;
//    repo->material_list.length ++;
    add(&repo->material_list, element);
}

void delete_material(Repository* repo, int position){
//    if(&repo->material_list == NULL){
//        return;
//    }
//    if(repo->material_list.elements == NULL){
//        return;
//    }
//    if(position < repo->material_list.length){
//        repo->material_list.length = repo->material_list.length - 1;
//        for(int i = position; i < repo->material_list.length; i++){
//            repo->material_list.elements[i] = repo->material_list.elements[i+1];
//        }
//    }
    delete(&repo->material_list, position);
}

void update_material(Repository* repo, int position, int new_quantity){
    update(&repo->material_list, position, new_quantity);
    //set_quantity(&repo->material_list.elements[position], new_quantity);
}

void load_new_container(Repository* repo, Dynamic_Array* new_container){
    destroy_dynamic_array(&repo->material_list);
    repo->material_list.capacity = new_container->capacity;
    repo->material_list.length = new_container->length;
    repo->material_list.elements = (Material*)malloc(100*sizeof(Material));

    if(repo->material_list.elements == NULL){
        return;
    }

    for(int i = 0; i < new_container->length; i ++){
        repo->material_list.elements[i] = new_container->elements[i];
    }
}