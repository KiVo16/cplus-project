//
// Created by Jakub Kurek on 09/04/2025.
//

#ifndef MICROMOUSESENSOR_H
#define MICROMOUSESENSOR_H


class MicromouseSensor {
public:
    virtual bool canMove(int fromX, int fromY, int toX, int toY);
};


#endif //MICROMOUSESENSOR_H

