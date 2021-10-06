cmake_minimum_required(VERSION 3.17)
project(a23_911_buiciuc_andrei C)

set(CMAKE_C_STANDARD 11)

add_executable(a23_911_buiciuc_andrei
        Domain/material.c Domain/material.h main.c UserInterface/user_interface.c UserInterface/user_interface.h Controller/controller.c Controller/controller.h Repository/repository.c Repository/repository.h Repository/test_init.c Repository/test_init.h Validator/validator_material.c Validator/validator_material.h Validator/validator_command.c Validator/validator_command.h Repository/test_dynamic_array.c Repository/test_dynamic_array.h Controller/undo_controller.h Controller/undo_controller.c Domain/test_material.c Domain/test_material.h Repository/test_repository.c Repository/test_repository.h Controller/test_controller.c Controller/test_controller.h Controller/test_undo.c Controller/test_undo.h Validator/test_validator.c Validator/test_validator.h Repository/dynamic_array.c Repository/dynamic_array.h)
