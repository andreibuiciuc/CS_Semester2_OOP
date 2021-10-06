#include "undo_controller.h"
#include <assert.h>

void test_create_destroy_undo_controller(){
    Undo_Controller* undoController = create_undo_controller(2,2);
    assert(undoController != NULL);
    assert(undoController->history_length == 0);
    assert(undoController->history_capacity == 2);
    assert(undoController->max_length == 0);
    assert(undoController->index == -1);
    assert(undoController->history != NULL);
    destroy_undo_controller(undoController);
}

void test_record_resize_undo_controller(){
    Undo_Controller* undoController = create_undo_controller(2,2);
    Repository* repo = create_repository(5);

    Material m1 = create_material("material", "supp", 100, create_expiration_date(2000,2,2));
    add_material(repo, m1);
    record(undoController, repo);

    Material m2 = create_material("material2", "supp2", 200, create_expiration_date(2004,4,4));
    add_material(repo, m2);
    record(undoController, repo);

    assert(undoController->history_length == 2);
    assert(undoController->max_length == 2);
    assert(undoController->index == 1);

    assert(undoController->history_capacity == 2);
    resize_undo(undoController);
    assert(undoController->history_capacity == 4);

    destroy_repository(repo);
    destroy_undo_controller(undoController);
}

void test_undo_redo(){
    Undo_Controller* undoController = create_undo_controller(2,2);
    Repository* repo = create_repository(5);

    Material m1 = create_material("material", "supp", 100, create_expiration_date(2000,2,2));
    add_material(repo, m1);
    record(undoController, repo);

    Material m2 = create_material("material2", "supp2", 200, create_expiration_date(2004,4,4));
    add_material(repo, m2);
    record(undoController, repo);

    assert(undoController->history_length == 2);

    undo(undoController, repo);
    assert(undoController->history_length == 1);
    undo(undoController, repo);
    assert(undoController->history_length == 1);
    redo(undoController, repo);
    assert(undoController->history_length == 2);

    destroy_repository(repo);
    destroy_undo_controller(undoController);
}

void test_undo_controller(){
    test_create_destroy_undo_controller();
    test_record_resize_undo_controller();
    test_undo_redo();
}
