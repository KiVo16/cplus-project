#ifndef MAZE_H
#define MAZE_H
#include <vector>


/// representation of cell
struct Cell {
    bool walls[4]{}; /// 0=North, 1=East,2=South,3=West.
    Cell() {
        walls[0] = walls[1] = walls[2] = walls[3] = true;
    }
};

typedef std::vector<std::vector<Cell> > MazeGrid;

/// class representing Maze
class Maze {
public:
    Maze(int rows, int cols);

    /**
     * connect 2 cells based on coordinates
     * @param x1 x-coordinate of first cell
     * @param y1 y-coordinate of first cell
     * @param x2 x-coordinate of second cell
     * @param y2 y-coordinate of second cell
     * @return true when cells were connected, false otherwise
     */
    bool connectCells(int x1, int y1, int x2, int y2);

    /**
     * checks if 2 cells are connected
     * @param x1 x-coordinate of first cell
     * @param y1 y-coordinate of first cell
     * @param x2 x-coordinate of second cell
     * @param y2 y-coordinate of second cell
     * @return true when cells are connected, false otherwise
     */
    bool areCellsConnected(int x1, int y1, int x2, int y2) const;

    /**
     * cell getter
     * @param x x-coordinate
     * @param y y-coordinate
     * @return pointer to Cell, pointer is null when cell is not found
     */
    const Cell *getCell(int x, int y) const;

    /**
     * rows count getter
     * @return rows count
     */
    size_t getRowsCount() const;

    /**
     * columns count getter
     * @return columns count
     */
    size_t getColsCount() const;

    /**
     * total cells count getter
     * @return all cells count
     */
    size_t getTotalCells() const;
private:
    /// maze grid representing maze
    MazeGrid grid;
};


#endif //MAZE_H
