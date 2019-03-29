cmake_minimum_required (VERSION 3.8)

set ( SRC_FILE src/Df1.cpp src/Df1Serial.cpp src/common.cpp src/read.cpp src/write.cpp)
set ( HED_FILE inc/Df1.h inc/Df1Serial.h)

include_directories ( "inc/" )

add_library( libdf1  ${SRC_FILE} ${HED_FILE})
qt5_use_modules(libdf1 SerialPort)
