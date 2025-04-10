#ifndef MICROMOUSESENSOR_H
#define MICROMOUSESENSOR_H


class MicromouseSensor {
public:
    virtual ~MicromouseSensor() = default;

    /**
     * checks if micromouse can be moved between two locations
     * @param fromX first location x coordinate
     * @param fromY first location y coordinate
     * @param toX second location x coordinate
     * @param toY second location y coordinate
     */
    virtual bool canMove(int fromX, int fromY, int toX, int toY) {
        return false;
    };
};


#endif //MICROMOUSESENSOR_H

