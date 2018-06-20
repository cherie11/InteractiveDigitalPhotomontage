project( project )

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

find_package( OpenCV REQUIRED )
find_package(Qt5Widgets CONFIG REQUIRED)
add_executable( project imageeditor.cpp image.cpp mainwindow.cpp main.cpp )
target_link_libraries( project ${OpenCV_LIBS} )
target_link_libraries( project Qt5::Widgets)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )
