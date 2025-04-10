#include "MazeGenerator.h"
#include "../Maze.h"

MazeGenerator::MazeGenerator(const int rows, const int cols)
    : currentRow(0), currentCol(0), finished(false), maze(std::make_unique<Maze>(rows, cols)) {
}

bool MazeGenerator::wereCoordinatesVisited(int x, int y) const {
    return visitedCoordinates.contains(std::make_pair(x, y));
}

void MazeGenerator::markCoordinatesAsVisited(int x, int y) {
    visitedCoordinates.insert(std::make_pair(std::make_pair(x, y), true));
}


size_t MazeGenerator::countVisitedCells() const {
    return visitedCoordinates.size();
}

VisitedCoordinates MazeGenerator::getVisitedCoordinates() const {
    return visitedCoordinates;
}

QPoint MazeGenerator::getCurrentCell() const { return {currentRow, currentCol}; }


void MazeGenerator::finishInstantly() {
    while (!this->isFinished()) {
        this->step();
    }
}

bool MazeGenerator::isFinished() const { return finished; }
const std::unique_ptr<Maze> &MazeGenerator::getMaze() const { return maze; }

