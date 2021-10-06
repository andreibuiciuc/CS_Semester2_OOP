#pragma once
#include "../Domain/material.h"

typedef Material TElem;

typedef struct{
    TElem* elements;
    int length; //  actual size of the array
    int capacity;
}Dynamic_Array;


/// Creates the dynamic array.
/// \param capacity
/// \return
Dynamic_Array create_dynamic_array(int capacity);


/// \summary Destroys the dynamic array.
/// \param array
void destroy_dynamic_array(Dynamic_Array* array);


/// \summary Resizes the dynamic array.
/// \param array
void resize_dynamic_array(Dynamic_Array* array);


/// \summary Adds a element to the array.
/// \param array
/// \param material
void add(Dynamic_Array* array, TElem element);


/// \summary Deletes an element from the array.
/// \param array
/// \param position
void delete(Dynamic_Array* array, int position);


/// \summary Updates an element from the array at a given position
/// \param array
/// \param position
/// \param new_quantity
void update(Dynamic_Array* array, int position, int new_quantity);