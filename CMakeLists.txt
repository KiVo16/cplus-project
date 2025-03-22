cmake_minimum_required(VERSION 3.30)
project(untitled6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/jk/Qt/6.8.2/macos")

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(untitled6 main.cpp
        MicromouseController.cpp
        MicromouseController.h
        MainWindow.cpp
        MainWindow.h
        MazeVisualizer.cpp
        MazeVisualizer.h
        MazeGenerator.cpp
        MazeGenerator.h
        AldousBroderMazeGenerator.cpp
        AldousBroderMazeGenerator.h
        RecursiveBacktracker.cpp
        RecursiveBacktracker.h
        PrimsMazeGenerator.cpp
        PrimsMazeGenerator.h
        WallFollowerController.cpp
        WallFollowerController.h
        FloodFillMicromouseController.cpp
        FloodFillMicromouseController.h
)
target_link_libraries(untitled6
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

