#ifndef FLOODFILLMICROMOUSECONTROLLER_H
#define FLOODFILLMICROMOUSECONTROLLER_H

#include "MicromouseController.h"

class FloodFillMicromouseController final : public MicromouseController {
public:
    explicit FloodFillMicromouseController(std::unique_ptr<Micromouse> &micromouse, QPoint goal): MicromouseController(micromouse, goal) {};

    void step() override;
};




#endif //FLOODFILLMICROMOUSECONTROLLER_H
