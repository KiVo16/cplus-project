//
// Created by Jakub Kurek on 19/03/2025.
//

#ifndef PRIMSMAZEGENERATOR_H
#define PRIMSMAZEGENERATOR_H



#include "MazeGenerator.h"
#include <vector>
#include <QPoint>

class PrimsMazeGenerator : public MazeGenerator {
public:
    PrimsMazeGenerator(int rows, int cols);
    bool step() override;
    QPoint getCurrentCell() const override;
private:
    struct Edge {
        int fromRow, fromCol;
        int toRow, toCol;
        int direction; // Direction from "from" cell to "to" cell.
    };
    std::vector<Edge> edgeList;
    int currentRow, currentCol;
    void addEdges(int row, int col);
};



#endif //PRIMSMAZEGENERATOR_H
