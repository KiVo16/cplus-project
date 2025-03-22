
//
// Created by Jakub Kurek on 21/03/2025.
//

#ifndef FLOODFILLMICROMOUSECONTROLLER_H
#define FLOODFILLMICROMOUSECONTROLLER_H

#include "MicromouseController.h"

class FloodFillMicromouseController : public MicromouseController {
public:
    explicit FloodFillMicromouseController();
    void setup(const Maze &m, const QPoint &start, const QPoint &goal) override;
    void step() override;
    QPoint currentPosition() const override;
    int currentOrientation() const override;
    std::vector<MicrmouseStep> path() const override;
private:
    Maze maze;
    QPoint pos;
    int orientation;
    std::vector<MicrmouseStep> pathTaken;
    QPoint goal;
    bool isSetup = false;


    // For demonstration: two-sided check, then move in direction that reduces manhattan distance.
    bool canMove(int fromR, int fromC, int toR, int toC);
};




#endif //FLOODFILLMICROMOUSECONTROLLER_H
