cmake_minimum_required (VERSION 3.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(SRC_FILE src/mainwindow.cpp src/main.cpp src/df1client.cpp)
set(HED_FILE inc/mainwindow.h inc/df1client.h)

include_directories("inc/")

add_executable(df1viewer ${SRC_FILE} ${HED_FILE})
qt5_use_modules(df1viewer Widgets WebSockets)
