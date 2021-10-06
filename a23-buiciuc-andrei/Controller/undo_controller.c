#include "undo_controller.h"
#include "controller.h"
#include "../Repository/repository.h"
#include <stdlib.h>
#include <stdio.h>

Undo_Controller* create_undo_controller(int history_capacity, int repo_capacity){
    Undo_Controller* undo_controller = (Undo_Controller*)malloc(sizeof(Undo_Controller));
    if(undo_controller == NULL){
        return NULL;
    }

    undo_controller->history_capacity = history_capacity;
    undo_controller->history_length = 0;
    undo_controller->index = -1;
    undo_controller->max_length = 0;

    undo_controller->history = (Dynamic_Array**)malloc(history_capacity*sizeof(Dynamic_Array*));
    for(int i = 0; i < history_capacity; i ++){
        undo_controller->history[i] = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
        undo_controller->history[i]->elements = (Material*)malloc(repo_capacity*sizeof(Material));
    }

    return undo_controller;
}

void destroy_undo_controller(Undo_Controller* undo_controller){
    for(int i = 0; i < undo_controller->history_capacity; i++){
        free(undo_controller->history[i]->elements);
        free(undo_controller->history[i]);
    }
    free(undo_controller->history);
    free(undo_controller);
}

void resize_undo(Undo_Controller* undo_controller){
    undo_controller->history_capacity = undo_controller->history_capacity * 2;
    Dynamic_Array** history = (Dynamic_Array**)malloc(undo_controller->history_capacity * sizeof(Dynamic_Array*));

    for(int i = 0; i < undo_controller->history_capacity; i ++){
        history[i] = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
        history[i]->elements = (Material*)malloc(100 * sizeof(Material));
    }

    for(int i = 0; i < undo_controller->history_capacity / 2; i ++){
        free(undo_controller->history[i]->elements);
        free(undo_controller->history[i]);
    }
    free(undo_controller->history);
    undo_controller->history = history;


}

void record(Undo_Controller* undo_controller, Repository* repository){
    undo_controller->index += 1;

    if(undo_controller->history_length == undo_controller->history_capacity){
        resize_undo(undo_controller);
    }


    undo_controller->history[undo_controller->history_length]->length = repository->material_list.length;
    undo_controller->history[undo_controller->history_length]->capacity = repository->material_list.capacity;
    for(int i = 0; i < repository->material_list.length; i ++){
        undo_controller->history[undo_controller->history_length]->elements[i] = repository->material_list.elements[i];
    }

    undo_controller->history_length += 1;

    if(undo_controller->history_length > undo_controller->max_length){
        undo_controller->max_length = undo_controller->history_length;
    }

}

int undo(Undo_Controller* undo_controller, Repository* repository){
   if(undo_controller->index == 0){
       return -1;
   }
   else {
       undo_controller->index -= 1;
       undo_controller->history_length -= 1;

       load_new_container(repository, undo_controller->history[undo_controller->index]);
       return 1;
   }
}

int redo(Undo_Controller* undo_controller, Repository* repository){
    if(undo_controller->index == undo_controller->max_length - 1){
        return -1;
    }
    else {
        undo_controller->index += 1;
        undo_controller->history_length += 1;

        load_new_container(repository, undo_controller->history[undo_controller->index]);
        return 1;
    }
}



