#include "Controller.h"

#include "Maze/Generator/AldousBroderMazeGenerator.h"
#include "Maze/Generator/PrimsMazeGenerator.h"
#include "Maze/Generator/RecursiveBacktracker.h"
#include "Micromouse/Controller/FloodFillMicromouseController.h"
#include "Micromouse/Controller/WallFollowerController.h"
#include "Micromouse/Sensor/LambdaSensor.h"
#include "Visualizer/Visualizer.h"

Controller::Controller(Visualizer *visualizer)
    : visualizer(visualizer), timerMaze(new Timer()), timerMicroMouse(new Timer()) {
}

void Controller::setMazeSize(int size) {
    this->mazeSize = size;
}

void Controller::startMazeGeneration(const MazeGeneratorType mazeGeneratorType, const SolutionPoint sp) {
    setupMazeGenerator(mazeGeneratorType);
    setupStartEndPoint(sp);
    timerMaze->start([this]() { this->updateMaze(); }, std::chrono::milliseconds(5));
    micromouseController = nullptr;
}

void Controller::setupMazeGenerator(const MazeGeneratorType mazeGeneratorType) {
    std::unique_ptr<MazeGenerator> mazeGenerator = nullptr;
    const int rows = mazeSize;
    const int cols = mazeSize;
    switch (mazeGeneratorType) {
        case MazeGeneratorType::AldousBroder:
            mazeGenerator = std::make_unique<AldousBroderMazeGenerator>(rows, cols);
            break;
        case MazeGeneratorType::Prims:
            mazeGenerator = std::make_unique<PrimsMazeGenerator>(rows, cols);
            break;
        case MazeGeneratorType::RecursiveBacktracking:
            mazeGenerator = std::make_unique<RecursiveBacktracker>(rows, cols);
            break;
        default:
            mazeGenerator = std::make_unique<RecursiveBacktracker>(rows, cols);
    }

    this->mazeGenerator = std::move(mazeGenerator);
}

void Controller::startMicromouse(const MicromouseControllerType micromouseControllerType) {
    if (!mazeGenerator || !mazeGenerator->isFinished()) return;
    micromouseController.reset();
    micromouse.reset();
    setupMicromouse(micromouseControllerType);
    timerMaze->start([this]() { this->updateMicromouse(); }, std::chrono::milliseconds(5));
}

void Controller::setupMicromouse(const MicromouseControllerType micromouseControllerType) {
    std::unique_ptr<MicromouseController> micromouseController = nullptr;
    micromouse = std::make_unique<Micromouse>(
        std::make_unique<LambdaSensor>(
            [this](const int fromR, const int fromC, const int toR,
                   const int toC) {
                return mazeGenerator->getMaze()->areCellsConnected(
                    fromC, fromR, toC, toR);
            }),
        startPoint
    );

    switch (micromouseControllerType) {
        case MicromouseControllerType::WallFollower:
            micromouseController = std::make_unique<WallFollowerController>(micromouse, solutionPoint);
            break;
        case MicromouseControllerType::FloodFill:
            micromouseController = std::make_unique<FloodFillMicromouseController>(micromouse, solutionPoint, mazeSize);
            break;
        default:
            micromouseController = std::make_unique<WallFollowerController>(micromouse, solutionPoint);
    }

    this->micromouseController = std::move(micromouseController);
}


void Controller::setupStartEndPoint(SolutionPoint sp) {
    if (!mazeGenerator) return;
    const auto &mazeData = mazeGenerator->getMaze();
    const auto rows = mazeData->getRowsCount() - 1;
    const auto cols = mazeData->getColsCount() - 1;

    switch (sp) {
        case SolutionPoint::TOP_LEFT:
            solutionPoint = QPoint(0, 0);
            startPoint = QPoint(cols, rows);
            break;
        case SolutionPoint::TOP_RIGHT:
            solutionPoint = QPoint(0, rows);
            startPoint = QPoint(cols, 0);
            break;
        case SolutionPoint::BOTTOM_LEFT:
            solutionPoint = QPoint(cols, 0);
            startPoint = QPoint(0, rows);
            break;
        case SolutionPoint::BOTTOM_RIGHT:
            solutionPoint = QPoint(cols, rows);
            startPoint = QPoint(0, 0);
            break;
        case SolutionPoint::CENTER:
            solutionPoint = QPoint(cols / 2, rows / 2);
            startPoint = QPoint(0, 0);
            break;
    }
}

void Controller::updateMaze() const {
    if (!mazeGenerator) return;
    if (!mazeGenerator->isFinished()) mazeGenerator->step();
    else {
        timerMaze->stop();
        signal.emitSignal(ControllerSignal::MAZE_GENERATION_FINISHED);
    }
    draw();
}

void Controller::updateMicromouse() const {
    if (!micromouseController) return;
    if (!micromouseController->isFinished()) micromouseController->step();
    else {
        timerMicroMouse->stop();
        signal.emitSignal(ControllerSignal::MICROMOUSE_FINISHED);
    }
    draw();
}

void Controller::skipMazeGenerationVisualisation() const {
    if (!mazeGenerator) return;
    timerMaze->stop();
    mazeGenerator->finishInstantly();
    signal.emitSignal(ControllerSignal::MAZE_GENERATION_FINISHED);
    draw();
}

void Controller::draw() const {
    MazeGeneratorVisualizationData *mazeData = nullptr;
    MicrmouseVisualizationData *micromouseData = nullptr;

    if (mazeGenerator) {
        mazeData = new MazeGeneratorVisualizationData{
            .maze = mazeGenerator->getMaze(),
            .current = mazeGenerator->getCurrentCell(),
            .startPoint = startPoint,
            .solutionPoint = solutionPoint,
            .isFinished = mazeGenerator->isFinished(),
            .visitedCoordinates = mazeGenerator->getVisitedCoordinates()
        };
    }

    if (micromouseController) {
        micromouseData = new MicrmouseVisualizationData{
            .path = micromouse->getPath(),
            .currentOrientation = micromouse->getCurrentOrientation(),
            .currentPosition = micromouse->getCurrentPosition(),
        };
    }

    visualizer->draw(mazeData, micromouseData);
}
