
//
// Created by Jakub Kurek on 20/03/2025.
//

#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H



#include <vector>
#include <QPoint>


enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

struct Cell {
    bool visited;
    bool walls[4]; // 0 = North, 1 =East, 2 =South, 3 = West.
    Cell() : visited(false) {
        walls[0] = walls[1] = walls[2] = walls[3] = true;
    }
};

typedef std::vector<std::vector<Cell>> Maze;

class MazeGenerator {
public:
    MazeGenerator(int rows, int cols)
        : rows(rows), cols(cols), finished(false) {
        maze.resize(rows, std::vector<Cell>(cols));
    }
    virtual ~MazeGenerator() = default;
    virtual bool step() = 0;
    bool isFinished() const { return finished; }
    const std::vector<std::vector<Cell>>& getMaze() const { return maze; }
    std::vector<std::vector<Cell>>& getMazeRef() { return maze; }
    virtual QPoint getCurrentCell() const { return QPoint(-1, -1); }
    void finishInstantly() {
        while (!this->isFinished()) {
            this->step();
        }
    }
protected:
    int rows, cols;
    bool finished;
    std::vector<std::vector<Cell>> maze;
};



#endif //MAZEGENERATOR_H
