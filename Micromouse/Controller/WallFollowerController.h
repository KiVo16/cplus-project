#ifndef WALLFOLLOWERCONTROLLER_H
#define WALLFOLLOWERCONTROLLER_H

#include "MicromouseController.h"


class WallFollowerController final : public MicromouseController {
public:
    explicit WallFollowerController(std::unique_ptr<Micromouse> &micromouse, QPoint goal): MicromouseController(micromouse, goal) {};

    void step() override;
};

#endif //WALLFOLLOWERCONTROLLER_H
