#ifndef PRIMSMAZEGENERATOR_H
#define PRIMSMAZEGENERATOR_H

#include "MazeGenerator.h"
#include <vector>
#include <QPoint>

/// maze generator based on Prim's algorithm
class PrimsMazeGenerator final : public MazeGenerator {
public:
    PrimsMazeGenerator(int rows, int cols);
    bool step() override;
private:
    /// edge definition
    struct Edge {
        int fromRow, fromCol;
        int toRow, toCol;
        int direction;
    };

    /// vector of edges
    std::vector<Edge> edgeList;

    /**
     * adds edges between current cell and its neighbours
     * @param row x-axis coordinate
     * @param col y-axis coordinate
     */
    void addEdges(int row, int col);
};



#endif //PRIMSMAZEGENERATOR_H
