//
// Created by Jakub Kurek on 22/04/2025.
//

#ifndef RANDOMCONTROLLER_H
#define RANDOMCONTROLLER_H
#include "MicromouseController.h"


class RandomController final : public MicromouseController  {
public:
    explicit RandomController(std::unique_ptr<Micromouse> &micromouse, QPoint goal): MicromouseController(micromouse, goal) {
        srand(static_cast<unsigned>(std::time(nullptr)));
    };

    void step() override;
};



#endif //RANDOMCONTROLLER_H
