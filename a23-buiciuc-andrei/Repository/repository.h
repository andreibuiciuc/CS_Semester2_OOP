#pragma once
#include "../Domain/material.h"
#include "dynamic_array.h"


//typedef struct{
//    Material * elements;
//    int length; //  actual size of the array
//    int capacity;
//}Dynamic_Array;


typedef struct {
    Dynamic_Array material_list;
}Repository;


/// \summary: Creates the repository.
/// \param repo_capacity: the capacity of the repository
/// \return: pointer to the repository
Repository* create_repository(int repo_capacity);


/// \summary: Destroys the dynamic array.
/// \param: pointer to the dynamic array
void destroy_dynamic_array(Dynamic_Array* array);


/// \summary: Destroys the repository.
/// \param repository: pointer to the repository
void destroy_repository(Repository* repository);


/// \summary: Resizes the repository.
/// \param repository: Pointer to the repository.
void resize(Repository* repository);


/// \summary: Gets the dynamic array container.
/// \param repository: pointer to the repository
/// \return: the dynamic array container
Dynamic_Array get_data(Repository* repository);


/// \summary: Adds a material to the list of materials.
/// \param repository: pointer to the repository
/// \param element: the element to be added
void add_material(Repository* repository, Material element);


/// \summary: Deletes the material from a given position.
/// \param repository: pointer to the repository
/// \param position: the given position
void delete_material(Repository* repository, int position);


/// \summary: Updates the material from a given position with a new quantity.
/// \param repository: pointer to the repository
/// \param position: the given position
/// \param new_quantity: the new quantity
void update_material(Repository* repository, int position, int new_quantity);


/// \summary: Loads a new container in the repository.
/// \param repository: Pointer to the repository.
/// \param new_container: Pointer to the new container.
void load_new_container(Repository* repository, Dynamic_Array* new_container);