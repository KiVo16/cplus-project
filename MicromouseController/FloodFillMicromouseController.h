
//
// Created by Jakub Kurek on 21/03/2025.
//

#ifndef FLOODFILLMICROMOUSECONTROLLER_H
#define FLOODFILLMICROMOUSECONTROLLER_H

#include "MicromouseController.h"

class FloodFillMicromouseController final : public MicromouseController {
public:
    explicit FloodFillMicromouseController() = default;
    void step() override;
};




#endif //FLOODFILLMICROMOUSECONTROLLER_H
