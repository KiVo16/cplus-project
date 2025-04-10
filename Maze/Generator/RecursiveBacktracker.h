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
private:
    std::stack<QPoint> cellStack;
    std::vector<int> getUnvisitedNeighbors(int row, int col) const;
};
#endif //RECURSIVEBACKTRACKER_H
