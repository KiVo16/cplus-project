#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H


#include <map>
#include <vector>
#include <QPoint>

#include "../Maze.h"

enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };


typedef std::map<std::tuple<int, int>, bool> VisitedCoordinates;

/// class generating maze
class MazeGenerator {
public:
    MazeGenerator(int rows, int cols);

    virtual ~MazeGenerator() = default;

    /**
     * finished value getter
     * @return finished
     */
    bool isFinished() const;

    /**
     * generated maze getter
     * @return smart pointer reference to generated maze
     */
    const std::unique_ptr<Maze> &getMaze() const;

    /**
     * performs all steps until maze generation is finished in the loop
     * resulting in instant maze generation
     */
    void finishInstantly();

    /**
     * currently processing cell getter
     * @return coordinates pair
     */
    QPoint getCurrentCell() const;

    /**
     * all visited coordinates getter
     * @return map of visited coordinates
     */
    VisitedCoordinates getVisitedCoordinates() const;

    /**
     * performs single step in maze generation
     */
    virtual bool step() = 0;

protected:
    /// defined currently processed row
    int currentRow;

    /// defined currently processed column
    int currentCol;

    /// defined whether maze generation finished
    bool finished;

    /// smart pointer for maze object
    std::unique_ptr<Maze> maze;

    /**
     * check whether coordinates were visited/processed before
     * @param x x-axis coordinate
     * @param y y-axis coordinate
     * @return true when coordinates were visited, false otherwise
     */
    bool wereCoordinatesVisited(int x, int y) const;

    /**
     * marks a given coordinates as visited
     * @param x x-axis coordinate
     * @param y y-axis coordinate
     */
    void markCoordinatesAsVisited(int x, int y);

    /**
     * counts all visited cells
     * @return number of visited cells
     */
    size_t countVisitedCells() const;

private:
    /// visited coordinates map
    VisitedCoordinates visitedCoordinates = {};
};


#endif //MAZEGENERATOR_H
