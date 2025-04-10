#include "FloodFillMicromouseController.h"
#include <cmath>


void FloodFillMicromouseController::step() {
    if (finished) return;
    auto orientation = micromouse->getCurrentOrientation();
    auto pos = micromouse->getCurrentPosition();
    auto pathTaken = micromouse->getPath();

    // Simple approach: pick a neighbor that reduces manhattan distance to goal
    // if multiple neighbors reduce distance, pick one arbitrarily
    int curDist = std::abs(pos.x() - goal.x()) + std::abs(pos.y() - goal.y());
    int bestDir = -1;
    int bestVal = curDist;
    // directions: 0=north,1=east,2=south,3=west
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
    for (int d = 0; d < 4; ++d) {
        int rr = pos.x() + dx[d];
        int cc = pos.y() + dy[d];
        if (micromouse->getSensor()->canMove(pos.x(), pos.y(), rr, cc)) {
            int dist2 = std::abs(rr - goal.x()) + std::abs(cc - goal.y());
            if (dist2 < bestVal) {
                bestVal = dist2;
                bestDir = d;
            }
        }
    }
    if (bestDir != -1) {
        orientation = bestDir;
        pos = QPoint(pos.x() + dx[bestDir], pos.y() + dy[bestDir]);
        micromouse->rotate(orientation);
        micromouse->move(pos.x(), pos.y());
    } else {
        // If no improvement, just turn right
        orientation = (orientation + 1) % 4;
        micromouse->rotate(orientation);
    }

    if (pos == goal) finished = true;
}
