#include "PrimsMazeGenerator.h"
#include <cstdlib>
#include <ctime>

PrimsMazeGenerator::PrimsMazeGenerator(const int rows, const int cols)
    : MazeGenerator(rows, cols) {
    srand(static_cast<unsigned int>(time(nullptr)));
    currentRow = rand() % rows;
    currentCol = rand() % cols;

    markCoordinatesAsVisited(currentRow, currentCol);
    addEdges(currentRow, currentCol);
}

void PrimsMazeGenerator::addEdges(int row, int col) {
    if (row > 0 && !wereCoordinatesVisited(row - 1, col)) {
        const Edge edge = {row, col, row - 1, col, UP};
        edgeList.push_back(edge);
    }
    if (col < maze->getColsCount() - 1 && !wereCoordinatesVisited(row, col + 1)) {
        const Edge edge = {row, col, row, col + 1, RIGHT};
        edgeList.push_back(edge);
    }
    if (row < maze->getRowsCount() - 1 && !wereCoordinatesVisited(row + 1, col)) {
        const Edge edge = {row, col, row + 1, col, DOWN};
        edgeList.push_back(edge);
    }
    if (col > 0 && !wereCoordinatesVisited(row, col -1)) {
        const Edge edge = {row, col, row, col - 1, LEFT};
        edgeList.push_back(edge);
    }
}

bool PrimsMazeGenerator::step() {
    if (edgeList.empty()) {
        finished = true;
        return true;
    }
    const int idx = rand() % edgeList.size();
    const Edge edge = edgeList[idx];
    edgeList.erase(edgeList.begin() + idx);

    if (!wereCoordinatesVisited(edge.toRow, edge.toCol)) {
        maze->connectCells(edge.fromCol, edge.fromRow,  edge.toCol, edge.toRow );
        markCoordinatesAsVisited(edge.toRow, edge.toCol);
        currentRow = edge.toRow;
        currentCol = edge.toCol;
        addEdges(edge.toRow, edge.toCol);
    }

    return finished;
}
