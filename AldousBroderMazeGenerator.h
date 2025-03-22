//
// Created by Jakub Kurek on 20/03/2025.
//

#ifndef ALDOUSBRODERMAZEGENERATOR_H
#define ALDOUSBRODERMAZEGENERATOR_H


#include <vector>
#include <QPoint>

#include "MazeGenerator.h"

class AldousBroderMazeGenerator : public MazeGenerator {
public:
    AldousBroderMazeGenerator(int rows, int cols);
    bool step() override;
    QPoint getCurrentCell() const override;
private:
    int currentRow, currentCol;
    int visitedCells;
    int totalCells;
};


#endif //ALDOUSBRODERMAZEGENERATOR_H
