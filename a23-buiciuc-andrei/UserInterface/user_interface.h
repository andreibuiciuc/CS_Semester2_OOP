#pragma once
#include "../Controller/controller.h"
#include "../Controller/undo_controller.h"

typedef struct {
    Controller* controller;
    Undo_Controller *undo_controller;
}UserInterface;


/// \summary: Creates the user interface.
/// \param repo_capacity: the initial capacity of the repository
/// \return: pointer to the user interface
UserInterface* create_user_interface(int repo_capacity);


/// \summary: Destroys / De-allocates the user interface.
/// \param ui: pointer to the user interface
void destroy_user_interface(UserInterface* ui);


/// \summary: Start the program
/// \param ui: pointer to the user interface
void start(UserInterface* ui);
