//
// Created by Jakub Kurek on 21/03/2025.
//

#ifndef WALLFOLLOWERCONTROLLER_H
#define WALLFOLLOWERCONTROLLER_H
#include <qmetatype.h>

#include "MazeGenerator.h"
#include "MicromouseController.h"


class WallFollowerController : public MicromouseController {
public:
    explicit WallFollowerController();
    void setup(const Maze &m, const QPoint &start, const QPoint &goal) override;
    void step() override;
    QPoint currentPosition() const override;
    int currentOrientation() const override;
    std::vector<MicrmouseStep> path() const override;
private:
    Maze maze;
    QPoint pos;
    int orientation; // 0=North,1=East,2=South,3=West
    std::vector<MicrmouseStep> pathTaken;
    QPoint goal;
    bool isSetup = false;

    // Two-sided check
    bool canMove(int fromR, int fromC, int toR, int toC);
};

#endif //WALLFOLLOWERCONTROLLER_H
