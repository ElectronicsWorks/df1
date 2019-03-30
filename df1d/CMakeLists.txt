cmake_minimum_required (VERSION 3.8)

include_directories (${PROJECT_SOURCE_DIR}/libdf1/inc)


set ( SRC_FILE main.cpp)

add_executable( df1d  ${SRC_FILE} ${HED_FILE})
target_link_libraries(df1d libdf1)
qt5_use_modules( df1d SerialPort Widgets)
