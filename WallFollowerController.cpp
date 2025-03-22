#include "WallFollowerController.h"

#include <iostream>

#include "MazeGenerator.h"

WallFollowerController::WallFollowerController()
    : pos(0, 0), orientation(1), goal(0, 0) {
    pathTaken.push_back({
        pos = QPoint(0, 0),
        orientation = 1,
    });
}

void WallFollowerController::setup(const Maze &m, const QPoint &start, const QPoint &goal) {
    maze = m;
    this->goal = goal;
    this->pos = start;
    isSetup = true;
}

QPoint WallFollowerController::currentPosition() const {
    return pos;
}

int WallFollowerController::currentOrientation() const {
    return orientation;
}

std::vector<MicrmouseStep> WallFollowerController::path() const {
    return pathTaken;
}

// Helper: two-sided check
bool WallFollowerController::canMove(int fromR, int fromC, int toR, int toC) {
    // If out of bounds
    if (toR < 0 || toR >= (int) maze.size() || toC < 0 || toC >= (int) maze[0].size())
        return false;
    int dR = toR - fromR;
    int dC = toC - fromC;
    // Check current cell's wall & neighbor cell's opposite wall
    if (dR == -1 && dC == 0) {
        // going north
        if (maze[fromR][fromC].walls[0]) return false; // north wall of from cell
        if (maze[toR][toC].walls[2]) return false; // south wall of to cell
    } else if (dR == 1 && dC == 0) {
        // going south
        if (maze[fromR][fromC].walls[2]) return false;
        if (maze[toR][toC].walls[0]) return false;
    } else if (dR == 0 && dC == 1) {
        // going east
        if (maze[fromR][fromC].walls[1]) return false;
        if (maze[toR][toC].walls[3]) return false;
    } else if (dR == 0 && dC == -1) {
        // going west
        if (maze[fromR][fromC].walls[3]) return false;
        if (maze[toR][toC].walls[1]) return false;
    } else {
        return false;
    }
    return true;
}

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
    if (canMove(pos.x(), pos.y(), leftCell.x(), leftCell.y())) {
        turnLeft();
        pathTaken.push_back({
            pos, orientation
        });
        pos = leftCell;
        moved = true;
    }
    // else if front open, move forward
    else if (canMove(pos.x(), pos.y(), frontCell.x(), frontCell.y())) {
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
