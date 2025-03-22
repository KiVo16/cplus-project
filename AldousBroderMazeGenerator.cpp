#include "AldousBroderMazeGenerator.h"
#include <cstdlib>
#include <ctime>

AldousBroderMazeGenerator::AldousBroderMazeGenerator(int rows, int cols)
    : MazeGenerator(rows, cols)
{
    maze.resize(rows, std::vector<Cell>(cols));
    finished = false;
    totalCells = rows * cols;
    visitedCells = 1;
    srand(static_cast<unsigned int>(time(0)));
    // Start at a random cell.
    currentRow = rand() % rows;
    currentCol = rand() % cols;
    maze[currentRow][currentCol].visited = true;
}

bool AldousBroderMazeGenerator::step() {
    if (visitedCells >= totalCells) {
        finished = true;
        return true;
    }

    // Get all valid directions from the current cell.
    std::vector<int> directions;
    if (currentRow > 0) directions.push_back(UP);
    if (currentCol < cols - 1) directions.push_back(RIGHT);
    if (currentRow < rows - 1) directions.push_back(DOWN);
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

    // If the neighbor is unvisited, remove the wall.
    if (!maze[nextRow][nextCol].visited) {
        switch (dir) {
            case UP:
                maze[currentRow][currentCol].walls[0] = false;
                maze[nextRow][nextCol].walls[2] = false;
                break;
            case RIGHT:
                maze[currentRow][currentCol].walls[1] = false;
                maze[nextRow][nextCol].walls[3] = false;
                break;
            case DOWN:
                maze[currentRow][currentCol].walls[2] = false;
                maze[nextRow][nextCol].walls[0] = false;
                break;
            case LEFT:
                maze[currentRow][currentCol].walls[3] = false;
                maze[nextRow][nextCol].walls[1] = false;
                break;
        }
        maze[nextRow][nextCol].visited = true;
        visitedCells++;
    }

    // Move to the chosen neighbor.
    currentRow = nextRow;
    currentCol = nextCol;

    if (visitedCells >= totalCells)
        finished = true;

    return finished;
}

QPoint AldousBroderMazeGenerator::getCurrentCell() const {
    return {currentRow, currentCol};
}
