#ifndef LAMBDASENSOR_H
#define LAMBDASENSOR_H

#include <functional>

#include "MicromouseSensor.h"

class LambdaSensor final : public MicromouseSensor {
public:
    using CanMoveFn = std::function<bool(int fromX, int fromY, int toX, int toY)>;

    explicit LambdaSensor(const CanMoveFn &func): canMoveFn(func) {
    }

    bool canMove(const int fromX, const int fromY, const int toX, const int toY) override {
        return canMoveFn(fromX, fromY, toX, toY);
    }

private:
    CanMoveFn canMoveFn;
};


#endif //LAMBDASENSOR_H
