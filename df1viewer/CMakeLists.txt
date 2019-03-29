cmake_minimum_required (VERSION 3.8)

add_executable(df1 ${SRC_FILe} ${HED_FILE})
target_link_libraries(df1 Qt5::Widgets Qt5::SerialPort)
