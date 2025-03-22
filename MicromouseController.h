//
// Created by Jakub Kurek on 20/03/2025.
//

#ifndef MICROMOUSECONTROLLER_H
#define MICROMOUSECONTROLLER_H
#include <qobject.h>

#include "MazeGenerator.h"


struct MicrmouseStep {
    QPoint pos;
    int orientation;
};


class MicromouseController {
public:
    virtual ~MicromouseController() = default;
    explicit MicromouseController() = default;
    virtual void setup(const Maze &m, const QPoint &start, const QPoint &goal) = 0;
    virtual void step() = 0;
    virtual QPoint currentPosition() const = 0;
    virtual int currentOrientation() const = 0;
    virtual std::vector<MicrmouseStep> path() const = 0;
    bool isFinished() const { return finished; }
protected:
    bool finished = false;
};


#endif //MICROMOUSECONTROLLER_H
