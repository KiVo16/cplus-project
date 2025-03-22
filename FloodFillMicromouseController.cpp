#include "FloodFillMicromouseController.h"
#include <cmath>

FloodFillMicromouseController::FloodFillMicromouseController()
    : pos(0, 0), orientation(1), goal(0, 0) {
    pathTaken.push_back({
        pos = QPoint(0, 0),
        orientation = 1,
    });
}

void FloodFillMicromouseController::setup(const Maze &m, const QPoint &start, const QPoint &goal) {
    maze = m;
    this->goal = goal;
    this->pos = start;
    isSetup = true;
}

QPoint FloodFillMicromouseController::currentPosition() const {
    return pos;
}

int FloodFillMicromouseController::currentOrientation() const {
    return orientation;
}

std::vector<MicrmouseStep> FloodFillMicromouseController::path() const {
    return pathTaken;
}

bool FloodFillMicromouseController::canMove(int fromR, int fromC, int toR, int toC) {
    if (toR < 0 || toR >= (int) maze.size() || toC < 0 || toC >= (int) maze[0].size())
        return false;
    int dR = toR - fromR;
    int dC = toC - fromC;
    if (dR == -1 && dC == 0) {
        if (maze[fromR][fromC].walls[0]) return false;
        if (maze[toR][toC].walls[2]) return false;
    } else if (dR == 1 && dC == 0) {
        if (maze[fromR][fromC].walls[2]) return false;
        if (maze[toR][toC].walls[0]) return false;
    } else if (dR == 0 && dC == 1) {
        if (maze[fromR][fromC].walls[1]) return false;
        if (maze[toR][toC].walls[3]) return false;
    } else if (dR == 0 && dC == -1) {
        if (maze[fromR][fromC].walls[3]) return false;
        if (maze[toR][toC].walls[1]) return false;
    } else {
        return false;
    }
    return true;
}


void FloodFillMicromouseController::step() {
    if (!isSetup || finished) return;

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
        if (canMove(pos.x(), pos.y(), rr, cc)) {
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
        pathTaken.push_back({
            pos,
            orientation,
        });
    } else {
        // If no improvement, just turn right
        orientation = (orientation + 1) % 4;
        pathTaken.push_back({
            pos,
            orientation,
        });
    }

    if (pos == goal) finished = true;
}
