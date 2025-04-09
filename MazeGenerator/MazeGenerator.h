
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
    bool walls[4]{}; // 0 = North, 1 =East, 2 =South, 3 = West.
    Cell() : visited(false) {
        walls[0] = walls[1] = walls[2] = walls[3] = true;
    }
};

typedef std::vector<std::vector<Cell>> Maze;

class MazeGenerator {
public:
    MazeGenerator(const int rows, const int cols)
        : rows(rows), cols(cols), finished(false) {
        maze.resize(rows, std::vector<Cell>(cols));
    }
    virtual ~MazeGenerator() = default;

    bool isFinished() const { return finished; }
    const Maze& getMaze() const { return maze; }
    Maze& getMazeRef() { return maze; }
    void finishInstantly() {
        while (!this->isFinished()) {
            this->step();
        }
    }

    virtual QPoint getCurrentCell() const { return {-1, -1}; }
    virtual bool step() = 0;
protected:
    int rows, cols;
    bool finished;
    Maze maze;
};



#endif //MAZEGENERATOR_H
