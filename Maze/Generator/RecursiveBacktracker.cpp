#include "RecursiveBacktracker.h"
#include <QPoint>

RecursiveBacktracker::RecursiveBacktracker(const int rows, const int cols)
    : MazeGenerator(rows, cols) {
    currentRow = 0;
    currentCol = 0;
    markCoordinatesAsVisited(currentRow, currentCol);
    srand(static_cast<unsigned int>(time(nullptr)));
}

std::vector<int> RecursiveBacktracker::getUnvisitedNeighbors(const int row, const int col) const {
    std::vector<int> neighbors;
    if (row > 0 && !wereCoordinatesVisited(row - 1, col)) neighbors.push_back(UP);
    if (col < maze->getColsCount() - 1 && !wereCoordinatesVisited(row, col + 1))
        neighbors.push_back(RIGHT);
    if (row < maze->getRowsCount() - 1 && !wereCoordinatesVisited(row + 1, col))
        neighbors.push_back(DOWN);
    if (col > 0 && !wereCoordinatesVisited(row, col - 1))
        neighbors.push_back(LEFT);
    return neighbors;
}

bool RecursiveBacktracker::step() {
    if (countVisitedCells() >= maze->getTotalCells()) {
        finished = true;
        return true;
    }
    if (std::vector<int> neighbors = getUnvisitedNeighbors(currentRow, currentCol); !neighbors.empty()) {
        const int dir = neighbors[rand() % neighbors.size()];
        cellStack.emplace(currentRow, currentCol);
        auto nextRow = currentRow;
        auto nextCol = currentCol;
        switch (dir) {
            case UP:
                nextRow -= 1;
                break;
            case RIGHT:
                nextCol += 1;
                break;
            case DOWN:
                nextRow += 1;
                break;
            case LEFT:
                nextCol -= 1;
                break;
            default: ;
        }
        maze->connectCells(currentCol, currentRow, nextCol, nextRow);
        currentRow = nextRow;
        currentCol = nextCol;
        markCoordinatesAsVisited(currentRow, currentCol);
    } else if (!cellStack.empty()) {
        const QPoint p = cellStack.top();
        cellStack.pop();
        currentRow = p.x();
        currentCol = p.y();
    }
    return finished;
}
