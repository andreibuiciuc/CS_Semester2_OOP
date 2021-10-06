#include "dynamic_array.h"
#include <stdlib.h>

Dynamic_Array create_dynamic_array(int capacity){
    Dynamic_Array array;
    array.length = 0;
    array.capacity = capacity;
    array.elements = (TElem*)malloc(array.capacity * sizeof(TElem));

    return array;
}


void destroy_dynamic_array(Dynamic_Array* array){
    if (array == NULL)
        return;

    free(array->elements);
    array->elements = NULL;

    //free(array);
}


void resize_dynamic_array(Dynamic_Array* array){
    array->capacity = array->capacity * 2;
    TElem* new_elements = (TElem*)malloc(array->capacity * sizeof(TElem));

    for(int i = 0; i < array->length; i ++){
        new_elements[i] = array->elements[i];
    }

    free(array->elements);
    array->elements = new_elements;
}


void add(Dynamic_Array* array, TElem element){
    if(array == NULL){
        return;
    }
    if(array->elements == NULL){
        return;
    }
    if(array->length == array->capacity){
        resize_dynamic_array(array);
    }

    array->elements[array->length] = element;
    array->length += 1;
}


void delete(Dynamic_Array* array, int position){
    if(array == NULL){
        return;
    }
    if(array->elements == NULL){
        return;
    }
    if(position < array->length){
        array->length = array->length - 1;
        for(int i = position; i < array->length; i++){
            array->elements[i] = array->elements[i+1];
        }
    }
}


void update(Dynamic_Array* array, int position, int new_quantity){
    set_quantity(&array->elements[position], new_quantity);
}
