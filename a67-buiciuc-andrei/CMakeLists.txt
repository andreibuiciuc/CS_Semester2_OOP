cmake_minimum_required(VERSION 3.17)
project(a67_911_buiciuc_andrei)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(a67_911_buiciuc_andrei
        Domain/test_domain.cpp
        Domain/test_domain.h
        Domain/tutorial.cpp
        Domain/tutorial.h
        Repository/repository.h
        Repository/repository.cpp
        Controller/controllerAdmin.h
        Controller/controllerAdmin.cpp
        Controller/test_controller.h
        Controller/test_controller.cpp
        UserInterface/UI.h
        UserInterface/UI.cpp
        Validator/validator.h
        Validator/validator.cpp
        main.cpp Controller/controllerUser.cpp Controller/controllerUser.h Repository/fileRepository.cpp Repository/fileRepository.h Exception/customException.cpp Exception/customException.h Repository/AbstractWatchlist.cpp Repository/AbstractWatchlist.h)
