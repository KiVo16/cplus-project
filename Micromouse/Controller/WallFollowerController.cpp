#include "WallFollowerController.h"

#include <iostream>

void WallFollowerController::step() {
    if (finished) return;
    auto orientation = micromouse->getCurrentOrientation();
    auto pos = micromouse->getCurrentPosition();
    auto pathTaken = micromouse->getPath();

    auto turnLeft = [&]() { micromouse->rotate((orientation + 3) % 4); };
    auto turnRight = [&]() { micromouse->rotate((orientation + 1) % 4); };

    // compute left orientation
    int leftOrient = (orientation + 3) % 4;

    // figure out neighbor coords
    auto offset = [&](int orient) {
        switch (orient) {
            case 0: return QPoint(-1, 0); // north
            case 1: return QPoint(0, 1); // east
            case 2: return QPoint(1, 0); // south
            case 3: return QPoint(0, -1); // west
        }
        return QPoint(0, 0);
    };
    QPoint leftOff = offset(leftOrient);
    QPoint frontOff = offset(orientation);

    QPoint leftCell = pos + leftOff;
    QPoint frontCell = pos + frontOff;
    // pathTaken.push_back({
    //     pos, orientation
    // });
    bool moved = false;
    // if left open, turn left & move
    if (micromouse->getSensor()->canMove(pos.x(), pos.y(), leftCell.x(), leftCell.y())) {
        turnLeft();
        pos = leftCell;
        moved = true;
    }
    // else if front open, move forward
    else if (micromouse->getSensor()->canMove(pos.x(), pos.y(), frontCell.x(), frontCell.y())) {
        pos = frontCell;
        moved = true;
    } else {
        // turn right
        turnRight();
    }
    if (moved) micromouse->move(pos.x(), pos.y());
    if (pos == goal) {
        finished = true;
    }
}
