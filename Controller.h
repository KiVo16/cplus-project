#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "Utils/Signal.h"
#include "Utils/Timer.h"
#include "Maze/Generator/MazeGenerator.h"
#include "Micromouse/Controller/MicromouseController.h"
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

enum class MazeGeneratorType {
    AldousBroder,
    Prims,
    RecursiveBacktracking
};

enum class MicromouseControllerType {
    FloodFill,
    WallFollower
};

class Controller {
public:
    explicit Controller(Visualizer *visualizer);

    /**
     * sets up maze solution point, maze generator and start maze generation
     * @param mazeGeneratorType type of maze generator
     * @param point maze solution point.
     */
    void startMazeGeneration(MazeGeneratorType mazeGeneratorType, SolutionPoint point);

    /**
     * sets up micromouse controller and start path finding
     * @param micromouseControllerType type of micromouse controller
     */
    void startMicromouse(MicromouseControllerType micromouseControllerType);

    /**
     * allow to skip maze generation visualization. It performs all steps at once until maze is fully generated
    */
    void skipMazeGenerationVisualisation() const;

    /**
     * maze size setter
     * @param size maze size
    */
    void setMazeSize(int size);

    /// signal used to communicate events like MAZE_GENERATION_FINISHED and MICROMOUSE_FINISHED
    Signal<ControllerSignal> signal;
private:
    /// micromouse object controlled by micromouse controller
    std::unique_ptr<Micromouse> micromouse;

    /// visualizer used to visualize maze and micromouse
    Visualizer *visualizer;

    /// timer for maze generation. Allows to define generation step intervals.
    std::unique_ptr<Timer> timerMaze;

    /// timer for micromouse generation. Allows to define generation step intervals.
    std::unique_ptr<Timer> timerMicroMouse;

    /// defines maze starting point
    QPoint startPoint;

    /// defines maze solution point
    QPoint solutionPoint;

    /// injected maze generator
    std::unique_ptr<MazeGenerator> mazeGenerator = nullptr;

    /// injected micromouse controller
    std::unique_ptr<MicromouseController> micromouseController = nullptr;

    int mazeSize = 20;

    /**
     * triggers single step in maze generator
    */
    void updateMaze() const;

    /**
     * triggers single step in micromouse controller
    */
    void updateMicromouse() const;

    /**
     * sets up starting point and maze solution point
    */
    void setupStartEndPoint(SolutionPoint point);

    /**
     * uses Visualizer to draw scene
    */
    void draw() const;

    /**
     * sets up maze generator
     * @param mazeGeneratorType type of maze generator
     */
    void setupMazeGenerator(MazeGeneratorType mazeGeneratorType);

    /**
     * sets up micromouse controller
     * @param micromouseControllerType type of micromouse controller
     */
    void setupMicromouse(MicromouseControllerType micromouseControllerType);


};



#endif //CONTROLLER_H
