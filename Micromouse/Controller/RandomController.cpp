//
// Created by Jakub Kurek on 22/04/2025.
//

#include "RandomController.h"

void RandomController::step() {
    if (finished) return;

    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};

    int currentOrientation = micromouse->getCurrentOrientation();
    QPoint pos = micromouse->getCurrentPosition();

    int dirs[4] = { (currentOrientation + 3) % 4,
                     currentOrientation,
                     (currentOrientation + 1) % 4,
                     (currentOrientation + 2) % 4 };

    int chosenDir = -1;
    QPoint newPos;

    auto randDir = rand() % 4;
    int dir = dirs[randDir];
    newPos = QPoint(pos.x() + dx[dir], pos.y() + dy[dir]);
    if (micromouse->getSensor()->canMove(pos.x(), pos.y(), newPos.x(), newPos.y())) {
        chosenDir = dir;
    }

    if (chosenDir == -1)
        return;

    if (chosenDir != currentOrientation)
        micromouse->rotate(chosenDir);

    micromouse->move(newPos.x(), newPos.y());

    if (newPos == goal)
        finished = true;
}
