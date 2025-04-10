#ifndef ALDOUSBRODERMAZEGENERATOR_H
#define ALDOUSBRODERMAZEGENERATOR_H


#include <vector>
#include <QPoint>

#include "MazeGenerator.h"


class AldousBroderMazeGenerator final : public MazeGenerator {
public:
    AldousBroderMazeGenerator(int rows, int cols);
    bool step() override;
};


#endif //ALDOUSBRODERMAZEGENERATOR_H
