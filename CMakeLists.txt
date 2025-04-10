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
        Maze/Generator/MazeGenerator.cpp
        Maze/Generator/MazeGenerator.h
        Maze/Generator/AldousBroderMazeGenerator.cpp
        Maze/Generator/AldousBroderMazeGenerator.h
        Maze/Generator/RecursiveBacktracker.cpp
        Maze/Generator/RecursiveBacktracker.h
        Maze/Generator/PrimsMazeGenerator.cpp
        Maze/Generator/PrimsMazeGenerator.h
        Micromouse/Micromouse.cpp
        Micromouse/Micromouse.h
        Micromouse/Controller/MicromouseController.cpp
        Micromouse/Controller/MicromouseController.h
        Micromouse/Controller/WallFollowerController.cpp
        Micromouse/Controller/WallFollowerController.h
        Micromouse/Controller/FloodFillMicromouseController.cpp
        Micromouse/Controller/FloodFillMicromouseController.h
        Visualizer/Visualizer.cpp
        Visualizer/Visualizer.h
        Visualizer/QVisualizer.cpp
        Visualizer/QVisualizer.h
        Controller.cpp
        Controller.h
        MainWindow.cpp
        MainWindow.h
        Utils/Timer.cpp
        Utils/Timer.h
        Utils/Signal.cpp
        Utils/Signal.h
        Micromouse/Sensor/MicromouseSensor.cpp
        Micromouse/Sensor/MicromouseSensor.h
        Micromouse/Sensor/LambdaSensor.cpp
        Micromouse/Sensor/LambdaSensor.h
        Maze/Maze.cpp
        Maze/Maze.h
)
target_link_libraries(untitled6
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

