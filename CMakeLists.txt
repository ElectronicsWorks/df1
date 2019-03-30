cmake_minimum_required(VERSION 3.8)


project(df1)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5SerialPort REQUIRED)
find_package(Qt5WebSockets REQUIRED)

find_package(qmdnsengine REQUIRED)
include_directories( 
	${QT_INCLUDES}
	${Qt5SerialPort_INCLUDES}
	${Qt5WebSockets_INCLUDES}
)


add_subdirectory("libdf1")
add_subdirectory("df1d")
add_subdirectory("df1viewer")
