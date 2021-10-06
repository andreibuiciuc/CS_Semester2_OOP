#include "UserInterface/user_interface.h"
#include "Repository/test_init.h"
#include "Repository/test_dynamic_array.h"
#include "Domain/test_material.h"
#include "Validator/test_validator.h"
#include "Repository/test_repository.h"
#include "Controller/test_controller.h"
#include "Controller/test_undo.h"
#include <stdio.h>
#include <crtdbg.h>

int main()
{

    setbuf(stdout, NULL);

    UserInterface *UI = create_user_interface(100);

    test_dynamic_array();
    printf("Test dynamic array done.\n");
    test_domain();
    printf("Test domain done.\n");
    test_validator();
    printf("Test validator done.\n");
    test_repository();
    printf("Test repository done.\n");
    test_controller();
    printf("Test controller done.\n");
    test_undo_controller();
    printf("Test undo controller done.\n");

    test_init(UI->controller->repository);
    start(UI);
    destroy_user_interface(UI);

    _CrtDumpMemoryLeaks();

    return 0;
}