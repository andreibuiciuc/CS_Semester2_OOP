#pragma once
#include "../Repository/repository.h"


typedef struct {
    Repository* repository;
}Controller;


/// \summary: Creates the controller
/// \param repo_capacity: the initial capacity of the repository
/// \return: pointer to the controller
Controller* create_controller(int repo_capacity);


/// \summary: Destroys / De-allocate the controller
/// \param controller: pointer to the controller
void destroy_controller(Controller* controller);


/// \summary: Gets the repository
/// \param controller: pointer to the controller.
/// \return: pointer to the repository
Repository* get_repo(Controller* controller);


/// \summary: Finds a material based on the given name, supplier and expiration_date.
/// \param controller: pointer to the controller
/// \param name: the name of the material
/// \param supplier: the supplier
/// \param expiration_date: the expiration date
/// \return: 1 if the operation is successful, -1 otherwise
int find_material(Controller* controller, char name[], char supplier[], Date expiration_date);


/// \summary: Creates and adds a material to the list of materials.
/// \param controller: pointer to the controller
/// \param name: the name of the material
/// \param supplier: the supplier
/// \param quantity: the quantity
/// \param expiration_date: the expiration date
void add_element(Controller* controller, char name[], char supplier[], int quantity, Date expiration_date);


/// \summary: Deletes the material based on the given name, supplier and expiration date.
/// \param controller: pointer to the controller
/// \param name: the name of the material
/// \param supplier: the supplier
/// \param expiration_date: the expiration date
/// \return: 1 if the operation is successful, -1 otherwise
int delete_element(Controller* controller, char name[], char supplier[], Date expiration_date);


/// \summary: Updates the material based on the given name, supplier and expiration date.
/// \param controller: pointer to the controller
/// \param name: the name of the material
/// \param supplier: the supplier
/// \param expiration_date: the expiration date
/// \param new_quantity: the new quantity for update
/// \return: 1 if the operation is successful, -1 otherwise
int update_element(Controller* controller, char name[], char supplier[], Date expiration_date, int new_quantity);


/// \summary: Sorts the array based on the provided option.
/// \param materials_data: the array with materials to be sorted
/// \param array_length: the length of the array
/// \param option: an option from ["name", "supplier", "quantity"]
void sort_elements_options(Material materials_data[], int array_length, char option[]);


/// \summary: Creates an array of materials past their expiration date.
/// \param controller: pointer to the controller
/// \param materials_data: an array in which materials short on supply date are added
/// \param substring: a given substring to be searched for
/// \return: the length of the array
int elements_past_expiration(Controller* controller, Material materials_data[], char substring[]);


/// \summary: Creates an array of materials short on supply.
/// \param controller: pointer to the controller
/// \param materials_data: an array in which materials short on supply date are added
/// \param supply: a given supply value
/// \return: the length of the array
int elements_short_on_supply(Controller* controller, Material materials_data[], int supply);


/// \summary: Creates an array of materials from a given supplier.
/// \param controller: pointer to the controller
/// \param materials_data: an array in which materials from a given supplier are added
/// \param supplier: a given supplier
/// \return: the length of the array
int elements_from_a_supplier(Controller* controller, Material* materials_data, char supplier[]);