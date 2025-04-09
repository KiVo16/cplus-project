//
// Created by Jakub Kurek on 21/03/2025.
//

#ifndef WALLFOLLOWERCONTROLLER_H
#define WALLFOLLOWERCONTROLLER_H
#include <qmetatype.h>

#include "../MazeGenerator/MazeGenerator.h"
#include "MicromouseController.h"


class WallFollowerController final : public MicromouseController {
public:
    explicit WallFollowerController() = default;
    void step() override;
};

#endif //WALLFOLLOWERCONTROLLER_H
