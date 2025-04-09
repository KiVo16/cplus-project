//
// Created by Jakub Kurek on 08/04/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "Signal.h"
#include "Timer.h"
#include "MazeGenerator/MazeGenerator.h"
#include "MicromouseController/MicromouseController.h"
#include "Visualizer/Visualizer.h"

enum class SolutionPoint {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTER
};

enum class ControllerSignal {
    MAZE_GENERATION_FINISHED,
    MICROMOUSE_FINISHED,
};

class Controller {
public:
    explicit Controller(Visualizer *visualizer);
    void startMazeGeneration(MazeGenerator *mazeGenerator, SolutionPoint point);
    void startMicromouse(MicromouseController *micromouseController);
    void skipMazeGenerationVisualisation() const;
    Signal<ControllerSignal> signal;
private:
    Visualizer *visualizer;
    Timer *timerMaze;
    Timer *timerMicroMouse;
    int cellSize{};

    QPoint startPoint;
    QPoint solutionPoint;

    MazeGenerator *mazeGenerator = nullptr;
    MicromouseController *micromouseController = nullptr;

    void updateMaze() const;
    void updateMicromouse() const;
    void setupStartEndPoint(SolutionPoint point);
    void draw() const;
};



#endif //CONTROLLER_H
