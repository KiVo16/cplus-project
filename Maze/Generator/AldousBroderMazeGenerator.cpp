#include "AldousBroderMazeGenerator.h"
#include <cstdlib>
#include <ctime>

AldousBroderMazeGenerator::AldousBroderMazeGenerator(int rows, int cols)
    : MazeGenerator(rows, cols)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    currentRow = rand() % rows;
    currentCol = rand() % cols;
    markCoordinatesAsVisited(currentRow, currentCol);
}

bool AldousBroderMazeGenerator::step() {
    if (countVisitedCells() >= maze->getTotalCells()) {
        finished = true;
        return true;
    }

    std::vector<int> directions;
    if (currentRow > 0) directions.push_back(UP);
    if (currentCol < maze->getColsCount() - 1) directions.push_back(RIGHT);
    if (currentRow < maze->getRowsCount() - 1) directions.push_back(DOWN);
    if (currentCol > 0) directions.push_back(LEFT);

    // Choose a random direction.
    int dir = directions[rand() % directions.size()];
    int nextRow = currentRow, nextCol = currentCol;
    switch (dir) {
        case UP:    nextRow = currentRow - 1; break;
        case RIGHT: nextCol = currentCol + 1; break;
        case DOWN:  nextRow = currentRow + 1; break;
        case LEFT:  nextCol = currentCol - 1; break;
    }

    if (!wereCoordinatesVisited(nextRow, nextCol)) {
        maze->connectCells(currentCol, currentRow, nextCol, nextRow);
        markCoordinatesAsVisited(nextRow, nextCol);
    }

    currentRow = nextRow;
    currentCol = nextCol;

    if (countVisitedCells() >= maze->getTotalCells())
        finished = true;

    return finished;
}
