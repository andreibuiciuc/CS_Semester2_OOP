#pragma once
#include "../Repository/repository.h"
#include "../Controller/controller.h"

typedef struct {
    Dynamic_Array** history;
    int history_length;        // the current length of the history
    int history_capacity;     // the capacity of the history
    int index;               // points to the current 'repository' state
    int max_length;         // the maximum length of the history throughout the program

}Undo_Controller;


/// \summary: Creates an undo controller.
/// \param history_capacity: the initial capacity of the history
/// \param repo_capacity: the initial capacity of a repository
/// \return: pointer to the undo controller
Undo_Controller* create_undo_controller(int history_capacity, int repo_capacity);


/// \summary: Destroys / De-allocates the undo controller.
/// \param undo_controller: to the undo controller
void destroy_undo_controller(Undo_Controller* undo_controller);


/// \summary: Resizes the history from the undo controller.
/// \param undo_controller: pointer to the undo controller
void resize_undo(Undo_Controller* undo_controller);


/// \summary: Records in the history the current 'repository' state.
/// \param undo_controller: pointer to the undo controller
/// \param repository: pointer to the current repository
void record(Undo_Controller* undo_controller, Repository* repository);


/// \summary: Undoes the last operation.
/// \param undo_controller: pointer to the undo controller
/// \param repository: pointer to the current 'repository' state
/// \return: 1 if successful, -1 otherwise
int undo(Undo_Controller* undo_controller, Repository* repository);


/// \summary: Redoes the last operation.
/// \param undo_controller: pointer to the undo controller
/// \param repository: pointer to the current 'repository' state
/// \return: 1 if successful, -1 otherwise
int redo(Undo_Controller* undo_controller, Repository* repository);

