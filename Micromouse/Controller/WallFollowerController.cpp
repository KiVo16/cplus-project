#include "WallFollowerController.h"

#include <iostream>

void WallFollowerController::step() {
    if (finished) return;

    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};

    int currentOrientation = micromouse->getCurrentOrientation();
    QPoint pos = micromouse->getCurrentPosition();

    int order[4] = { (currentOrientation + 3) % 4,
                     currentOrientation,
                     (currentOrientation + 1) % 4,
                     (currentOrientation + 2) % 4 };

    int chosenDir = -1;
    QPoint newPos;

    for (int i = 0; i < 4; ++i) {
        int dir = order[i];
        newPos = QPoint(pos.x() + dx[dir], pos.y() + dy[dir]);
        if (micromouse->getSensor()->canMove(pos.x(), pos.y(), newPos.x(), newPos.y())) {
            chosenDir = dir;
            break;
        }
    }

    if (chosenDir == -1)
        return;

    if (chosenDir != currentOrientation)
        micromouse->rotate(chosenDir);

    micromouse->move(newPos.x(), newPos.y());

    if (newPos == goal)
        finished = true;
}
