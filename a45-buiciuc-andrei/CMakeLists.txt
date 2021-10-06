cmake_minimum_required(VERSION 3.17)
project(a45_911_buiciuc_andrei)

set(CMAKE_CXX_STANDARD 14)

add_executable(a45_911_buiciuc_andrei
        main.cpp Domain/tutorial.h Domain/tutorial.cpp Domain/test_domain.cpp Domain/test_domain.h UserInterface/UI.cpp UserInterface/UI.h Controller/controller.cpp Controller/controller.h Repository/repository.cpp Repository/repository.h Repository/dynamicArray.h Repository/test_dynamic_array.cpp Repository/test_dynamic_array.h Repository/test_repository.cpp Repository/test_repository.h Repository/test_init.cpp Repository/test_init.h Validator/validator.cpp Validator/validator.h Controller/test_controller.cpp Controller/test_controller.h Validator/test_validator.cpp Validator/test_validator.h)
