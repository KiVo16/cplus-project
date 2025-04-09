#include "PrimsMazeGenerator.h"
#include <cstdlib>
#include <ctime>

PrimsMazeGenerator::PrimsMazeGenerator(int rows, int cols)
    : MazeGenerator(rows, cols)
{
    maze.resize(rows, std::vector<Cell>(cols));
    finished = false;
    srand(static_cast<unsigned int>(time(0)));
    // Start at a random cell.
    currentRow = rand() % rows;
    currentCol = rand() % cols;
    maze[currentRow][currentCol].visited = true;
    addEdges(currentRow, currentCol);
}

void PrimsMazeGenerator::addEdges(int row, int col) {
    // Add each unvisited neighbor as an edge.
    if (row > 0 && !maze[row - 1][col].visited) {
        Edge edge = { row, col, row - 1, col, UP };
        edgeList.push_back(edge);
    }
    if (col < cols - 1 && !maze[row][col + 1].visited) {
        Edge edge = { row, col, row, col + 1, RIGHT };
        edgeList.push_back(edge);
    }
    if (row < rows - 1 && !maze[row + 1][col].visited) {
        Edge edge = { row, col, row + 1, col, DOWN };
        edgeList.push_back(edge);
    }
    if (col > 0 && !maze[row][col - 1].visited) {
        Edge edge = { row, col, row, col - 1, LEFT };
        edgeList.push_back(edge);
    }
}

bool PrimsMazeGenerator::step() {
    if (edgeList.empty()) {
        finished = true;
        return true;
    }
    // Choose a random edge.
    int idx = rand() % edgeList.size();
    Edge edge = edgeList[idx];
    // Remove the edge from the list.
    edgeList.erase(edgeList.begin() + idx);

    // If the target cell is not visited, remove the wall and add its edges.
    if (!maze[edge.toRow][edge.toCol].visited) {
        switch (edge.direction) {
            case UP:
                maze[edge.fromRow][edge.fromCol].walls[0] = false;
                maze[edge.toRow][edge.toCol].walls[2] = false;
                break;
            case RIGHT:
                maze[edge.fromRow][edge.fromCol].walls[1] = false;
                maze[edge.toRow][edge.toCol].walls[3] = false;
                break;
            case DOWN:
                maze[edge.fromRow][edge.fromCol].walls[2] = false;
                maze[edge.toRow][edge.toCol].walls[0] = false;
                break;
            case LEFT:
                maze[edge.fromRow][edge.fromCol].walls[3] = false;
                maze[edge.toRow][edge.toCol].walls[1] = false;
                break;
        }
        maze[edge.toRow][edge.toCol].visited = true;
        currentRow = edge.toRow;
        currentCol = edge.toCol;
        addEdges(edge.toRow, edge.toCol);
    }

    return finished;
}

QPoint PrimsMazeGenerator::getCurrentCell() const {
    return QPoint(currentRow, currentCol);
}
