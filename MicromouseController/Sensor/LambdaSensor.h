//
// Created by Jakub Kurek on 09/04/2025.
//

#ifndef LAMBDASENSOR_H
#define LAMBDASENSOR_H

#include <functional>

#include "MicromouseSensor.h"

class LambdaSensor : public MicromouseSensor {
public:
    using CanMoveFn = std::function<bool(int fromX, int fromY, int toX, int toY)>;

    explicit LambdaSensor(const CanMoveFn &func): canMoveFn(func) {
    }

    bool canMove(int fromX, int fromY, int toX, int toY) override {
        return canMoveFn(fromX, fromY, toX, toY);
    }

private:
    CanMoveFn canMoveFn;
};


#endif //LAMBDASENSOR_H
