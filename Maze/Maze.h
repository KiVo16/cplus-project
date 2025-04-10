#ifndef MAZE_H
#define MAZE_H
#include <vector>


struct Cell {
    bool walls[4]{}; // 0 = North, 1 =East, 2 =South, 3 = West.
    Cell() {
        walls[0] = walls[1] = walls[2] = walls[3] = true;
    }
};

typedef std::vector<std::vector<Cell> > MazeGrid;


class Maze {
public:
    Maze(int rows, int cols);
    bool connectCells(int x1, int y1, int x2, int y2);
    bool areCellsConnected(int x1, int y1, int x2, int y2) const;

    const Cell *getCell(int x, int y) const;
    size_t getRowsCount() const;
    size_t getColsCount() const;
    size_t getTotalCells() const;
private:
    MazeGrid grid;
};


#endif //MAZE_H
