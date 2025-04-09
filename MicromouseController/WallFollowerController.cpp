#include "WallFollowerController.h"

#include <iostream>

#include "../MazeGenerator/MazeGenerator.h"

void WallFollowerController::step() {
    if (!isSetup || finished) return;
    // orientation=0:North,1:East,2:South,3:West
    auto turnLeft = [&]() { orientation = (orientation + 3) % 4; };
    auto turnRight = [&]() { orientation = (orientation + 1) % 4; };

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
    pathTaken.push_back({
        pos, orientation
    });
    bool moved = false;
    // if left open, turn left & move
    if (sensor->canMove(pos.x(), pos.y(), leftCell.x(), leftCell.y())) {
        turnLeft();
        pathTaken.push_back({
            pos, orientation
        });
        pos = leftCell;
        moved = true;
    }
    // else if front open, move forward
    else if (sensor->canMove(pos.x(), pos.y(), frontCell.x(), frontCell.y())) {
        pos = frontCell;
        moved = true;
    } else {
        // turn right
        turnRight();
    }
    pathTaken.push_back({
        pos, orientation
    });

    // check if goal reached
    if (pos == goal) {
        finished = true;
    }
}
