//
// Created by Jakub Kurek on 20/03/2025.
//

#ifndef MICROMOUSECONTROLLER_H
#define MICROMOUSECONTROLLER_H
#include <qobject.h>

#include "../MazeGenerator/MazeGenerator.h"
#include "Sensor/LambdaSensor.h"
#include "Sensor/MicromouseSensor.h"

#include
#include


struct MicrmouseStep {
    QPoint pos;
    int orientation;
};

class MicromouseController {
public:
    virtual ~MicromouseController() = default;


    explicit MicromouseController() = default;

    void setup(const MicromouseSensor *sensor, const QPoint &start, const QPoint &goal) {
        isSetup = true;
        this->sensor = sensor;
        this->pos = start;
        this->goal = goal;
        this->orientation = 1;
    };

    virtual void step() = 0;

    QPoint currentPosition() const {
        return pos;
    };

    int currentOrientation() const {
        return orientation;
    };

    std::vector<MicrmouseStep> path() const {
        return pathTaken;
    };

    bool isFinished() const { return finished; }

protected:
    bool finished = false;
    bool isSetup = false;
    QPoint goal;
    MicromouseSensor *sensor;
    QPoint pos;
    int orientation = 1; // 0=North,1=East,2=South,3=West
    std::vector<MicrmouseStep> pathTaken;
};


#endif //MICROMOUSECONTROLLER_H
