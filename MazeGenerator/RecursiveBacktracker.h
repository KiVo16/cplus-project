
//
// Created by Jakub Kurek on 19/03/2025.
//

#ifndef RECURSIVEBACKTRACKER_H
#define RECURSIVEBACKTRACKER_H

#include "MazeGenerator.h"
#include <stack>
#include <QPoint>
#include <vector>

class RecursiveBacktracker final : public MazeGenerator {
public:
    RecursiveBacktracker(int rows, int cols);

    bool step() override;
    QPoint getCurrentCell() const override;
private:
    std::stack<QPoint> cellStack;
    int totalCells;
    int visitedCells;
    int currentRow;
    int currentCol;

    std::vector<int> getUnvisitedNeighbors(int row, int col) const;
};
#endif //RECURSIVEBACKTRACKER_H
