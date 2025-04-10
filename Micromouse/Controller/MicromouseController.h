#ifndef MICROMOUSECONTROLLER_H
#define MICROMOUSECONTROLLER_H

#include <iostream>
#include <ostream>

#include "../Micromouse.h"
#include "../Sensor/MicromouseSensor.h"


class MicromouseController {
public:
    virtual ~MicromouseController() = default;

    explicit MicromouseController(std::unique_ptr<Micromouse> &micromouse, QPoint goal): goal(goal), micromouse(micromouse) {};

    /**
     * performs single step in solution finding
     */
    virtual void step() {}

    /**
     * finished value getter
     * @return finished
     */
    bool isFinished() const;

protected:
    /// defined whether controller reached the goal position
    bool finished = false;

    /// goal position
    QPoint goal;

    /// smart pointer reference to micromouse
    std::unique_ptr<Micromouse> &micromouse;
};


#endif //MICROMOUSECONTROLLER_H
