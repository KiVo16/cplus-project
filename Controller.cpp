//
// Created by Jakub Kurek on 08/04/2025.
//

#include "Controller.h"

#include <iostream>

#include "MicromouseController/Sensor/LambdaSensor.h"
#include "Visualizer/Visualizer.h"

Controller::Controller(Visualizer *visualizer)
    : visualizer(visualizer), timerMaze(new Timer()), timerMicroMouse(new Timer()) {
}

void Controller::startMazeGeneration(MazeGenerator *mg, SolutionPoint sp) {
    mazeGenerator = mg;
    setupStartEndPoint(sp);
    timerMaze->start([this]() { this->updateMaze(); }, std::chrono::milliseconds(5));
    micromouseController = nullptr;
}

void Controller::startMicromouse(MicromouseController *mc) {
    if (!mazeGenerator || !mazeGenerator->isFinished()) return;
    micromouseController = mc;
    micromouseController->setup(new LambdaSensor([this](int fromR, int fromC, int toR, int toC) {
            auto maze = this->mazeGenerator->getMaze();
            if (toR < 0 || toR >= static_cast<int>(maze.size()) || toC < 0 || toC >= static_cast<int>(maze[0].size()))
                return false;
            int dR = toR - fromR;
            int dC = toC - fromC;
            if (dR == -1 && dC == 0) {
                if (maze[fromR][fromC].walls[0]) return false;
                if (maze[toR][toC].walls[2]) return false;
            } else if (dR == 1 && dC == 0) {
                if (maze[fromR][fromC].walls[2]) return false;
                if (maze[toR][toC].walls[0]) return false;
            } else if (dR == 0 && dC == 1) {
                if (maze[fromR][fromC].walls[1]) return false;
                if (maze[toR][toC].walls[3]) return false;
            } else if (dR == 0 && dC == -1) {
                if (maze[fromR][fromC].walls[3]) return false;
                if (maze[toR][toC].walls[1]) return false;
            } else {
                return false;
            }
            return true;
        }), startPoint, solutionPoint);
    timerMaze->start([this]() { this->updateMicromouse(); }, std::chrono::milliseconds(5));
}


void Controller::setupStartEndPoint(SolutionPoint sp) {
    if (!mazeGenerator) return;
    const auto &mazeData = mazeGenerator->getMaze();
    const auto rows = mazeData.size() - 1;
    const auto cols = mazeData[0].size() - 1;
    std::cout << rows << " " << cols << std::endl;
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
        };
    }

    if (micromouseController) {
        micromouseData = new MicrmouseVisualizationData{
            .path = micromouseController->path(),
            .currentOrientation = micromouseController->currentOrientation(),
            .currentPosition = micromouseController->currentPosition(),
        };
    }

    visualizer->draw(mazeData, micromouseData);
}
