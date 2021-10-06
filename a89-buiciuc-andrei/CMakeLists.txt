cmake_minimum_required(VERSION 3.17)
project(a89_911_buiciuc_andrei)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Charts)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)

include_directories(UserInterface)

add_executable(a89_911_buiciuc_andrei
        Domain/tutorial.cpp
        Domain/tutorial.h
        Repository/repository.cpp
        Repository/repository.h
        Repository/fileRepository.cpp
        Repository/fileRepository.h
        Repository/AbstractWatchlist.cpp
        Repository/AbstractWatchlist.h
        Controller/controllerAdmin.cpp
        Controller/controllerAdmin.h
        Controller/controllerUser.cpp
        Controller/controllerUser.h
        Controller/Action.cpp
        Controller/Action.h
        UserInterface/UI.cpp
        UserInterface/UI.h
        UserInterface/GUI.cpp
        UserInterface/GUI.h
        UserInterface/adminGUI.cpp
        UserInterface/adminGUI.h
        UserInterface/userGUI.cpp
        UserInterface/userGUI.h
        UserInterface/TutorialsTableModel.cpp
        UserInterface/TutorialsTableModel.h
        Validator/validator.cpp
        Validator/validator.h
        Exception/customException.cpp
        Exception/customException.h
        main.cpp)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})