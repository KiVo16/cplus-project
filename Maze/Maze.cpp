#include "Maze.h"

Maze::Maze(const int rows, const int cols) {
    grid.resize(rows, std::vector<Cell>(cols));
}

bool Maze::connectCells(const int x1, const int y1, const int x2, const int y2) {
    if (x1 == x2 && y1 == y2) return false;

    int w1 = 0, w2 = 0;

    // Down
    if (x1 == x2 && y2 > y1) w1 = 2, w2 = 0;
        // Up
    else if (x1 == x2 && y2 < y1) w1 = 0, w2 = 2;
        // Right
    else if (x2 > x1 && y1 == y2) w1 = 1, w2 = 3;
        // Left
    else if (x2 < x1 && y1 == y2) w1 = 3, w2 = 1;

    grid[x1][y1].walls[w1] = false;
    grid[x2][y2].walls[w2] = false;
    return true;
}

bool Maze::areCellsConnected(const int x1, const int y1, const int x2, const int y2) const {
    const auto c1 = getCell(y1, x1);
    const auto c2 = getCell(y2, x2);
    if (!c1 || !c2) return false;

    int w1 = 0, w2 = 0;
    // Down
    if (x1 == x2 && y2 > y1) w1 = 2, w2 = 0;
        // Up
    else if (x1 == x2 && y2 < y1) w1 = 0, w2 = 2;
        // Right
    else if (x2 > x1 && y1 == y2) w1 = 1, w2 = 3;
        // Left
    else if (x2 < x1 && y1 == y2) w1 = 3, w2 = 1;

    if (c1->walls[w1]) return false;
    if (c2->walls[w2]) return false;
    return true;
}

const Cell *Maze::getCell(int x, int y) const {
    if (y < 0 || y >= getRowsCount()) return nullptr;
    if (x < 0 || x >= getColsCount()) return nullptr;
    return &grid[y][x];
};

size_t Maze::getRowsCount() const {
    return grid.size();
};

size_t Maze::getColsCount() const {
    return grid[0].size();
};

size_t Maze::getTotalCells() const {
    return getRowsCount() * getColsCount();
};
