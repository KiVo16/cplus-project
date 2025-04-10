#ifndef PRIMSMAZEGENERATOR_H
#define PRIMSMAZEGENERATOR_H

#include "MazeGenerator.h"
#include <vector>
#include <QPoint>

class PrimsMazeGenerator final : public MazeGenerator {
public:
    PrimsMazeGenerator(int rows, int cols);
    bool step() override;
private:
    struct Edge {
        int fromRow, fromCol;
        int toRow, toCol;
        int direction;
    };
    std::vector<Edge> edgeList;
    void addEdges(int row, int col);
};



#endif //PRIMSMAZEGENERATOR_H
