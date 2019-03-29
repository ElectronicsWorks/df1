cmake_minimum_required(VERSION 3.8)


project(df1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5SerialPort REQUIRED)
include_directories( 
	${QT_INCLUDES}
)



add_subdirectory("libdf1")
#add_subdirectory("df1d")
#add_subdirectory("df1viewer")
