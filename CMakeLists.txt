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
        MazeGenerator/MazeGenerator.cpp
        MazeGenerator/MazeGenerator.h
        MazeGenerator/AldousBroderMazeGenerator.cpp
        MazeGenerator/AldousBroderMazeGenerator.h
        MazeGenerator/RecursiveBacktracker.cpp
        MazeGenerator/RecursiveBacktracker.h
        MazeGenerator/PrimsMazeGenerator.cpp
        MazeGenerator/PrimsMazeGenerator.h
        MicroMouseController/MicromouseController.cpp
        MicroMouseController/MicromouseController.h
        MicroMouseController/WallFollowerController.cpp
        MicroMouseController/WallFollowerController.h
        MicroMouseController/FloodFillMicromouseController.cpp
        MicroMouseController/FloodFillMicromouseController.h
        Visualizer/Visualizer.cpp
        Visualizer/Visualizer.h
        Visualizer/QVisualizer.cpp
        Visualizer/QVisualizer.h
        Controller.cpp
        Controller.h
        MainWindow.cpp
        MainWindow.h
        Timer.cpp
        Timer.h
        Signal.cpp
        Signal.h
        MicromouseController/Sensor/MicromouseSensor.cpp
        MicromouseController/Sensor/MicromouseSensor.h
        MicromouseController/Sensor/LambdaSensor.cpp
        MicromouseController/Sensor/LambdaSensor.h
)
target_link_libraries(untitled6
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

