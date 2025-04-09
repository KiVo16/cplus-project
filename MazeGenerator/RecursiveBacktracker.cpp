#include "RecursiveBacktracker.h"
#include <QPoint>

RecursiveBacktracker::RecursiveBacktracker(int rows, int cols)
    : MazeGenerator(rows, cols) {
    // Initialize the maze grid.
    maze.resize(rows, std::vector<Cell>(cols));
    finished = false;
    totalCells = rows * cols;
    visitedCells = 1;
    currentRow = 0;
    currentCol = 0;
    maze[currentRow][currentCol].visited = true;
    // Seed the random number generator.
    srand(static_cast<unsigned int>(time(0)));
}

std::vector<int> RecursiveBacktracker::getUnvisitedNeighbors(const int row, const int col) const {
    std::vector<int> neighbors;
    if (row > 0 && !maze[row - 1][col].visited)
        neighbors.push_back(UP);
    if (col < cols - 1 && !maze[row][col + 1].visited)
        neighbors.push_back(RIGHT);
    if (row < rows - 1 && !maze[row + 1][col].visited)
        neighbors.push_back(DOWN);
    if (col > 0 && !maze[row][col - 1].visited)
        neighbors.push_back(LEFT);
    return neighbors;
}

bool RecursiveBacktracker::step() {
    if (visitedCells >= totalCells) {
        finished = true;
        return true;
    }
    if (std::vector<int> neighbors = getUnvisitedNeighbors(currentRow, currentCol); !neighbors.empty()) {
        // Choose a random neighbor.
        const int dir = neighbors[rand() % neighbors.size()];
        cellStack.emplace(currentRow, currentCol);
        // Remove the wall between current cell and chosen neighbor.
        switch (dir) {
            case UP:
                maze[currentRow][currentCol].walls[0] = false;
                currentRow -= 1;
                maze[currentRow][currentCol].walls[2] = false;
                break;
            case RIGHT:
                maze[currentRow][currentCol].walls[1] = false;
                currentCol += 1;
                maze[currentRow][currentCol].walls[3] = false;
                break;
            case DOWN:
                maze[currentRow][currentCol].walls[2] = false;
                currentRow += 1;
                maze[currentRow][currentCol].walls[0] = false;
                break;
            case LEFT:
                maze[currentRow][currentCol].walls[3] = false;
                currentCol -= 1;
                maze[currentRow][currentCol].walls[1] = false;
                break;
            default: ;
        }
        maze[currentRow][currentCol].visited = true;
        visitedCells++;
    } else if (!cellStack.empty()) {
        // Backtrack.
        const QPoint p = cellStack.top();
        cellStack.pop();
        currentRow = p.x();
        currentCol = p.y();
    }
    if (visitedCells >= totalCells)
        finished = true;
    return finished;
}

QPoint RecursiveBacktracker::getCurrentCell() const {
    return {currentRow, currentCol};
}
