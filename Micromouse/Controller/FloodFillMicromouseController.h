#ifndef FLOODFILLMICROMOUSECONTROLLER_H
#define FLOODFILLMICROMOUSECONTROLLER_H

#include "MicromouseController.h"

class FloodFillMicromouseController final : public MicromouseController {
public:
    explicit FloodFillMicromouseController(std::unique_ptr<Micromouse> &micromouse, QPoint goal,
                                           int mazeSize): MicromouseController(
                                                                   micromouse, goal), mazeSize(mazeSize) {
    };

    void step() override;

private:
    int mazeSize;
};


#endif //FLOODFILLMICROMOUSECONTROLLER_H
