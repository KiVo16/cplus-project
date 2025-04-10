#ifndef MICROMOUSE_H
#define MICROMOUSE_H
#include <QPoint>


#include "Sensor/MicromouseSensor.h"

struct MicrmouseStep {
    QPoint pos;
    int orientation;
};

typedef std::vector<MicrmouseStep> MicromousePath;

class Micromouse final {
public:
    explicit Micromouse(std::unique_ptr<MicromouseSensor> sensor, QPoint start);

    /**
     * current position getter
     * @return current position
     */
    QPoint getCurrentPosition() const;;

    /**
     * current orientation getter
     * @return current orientation
     */
    int getCurrentOrientation() const;

    /**
     * path getter
     * @return MicromousePath
     */
    MicromousePath getPath() const;

    /**
     * sensor getter
     * @return reference to smart pointer
     */
    const std::unique_ptr<MicromouseSensor> &getSensor() const;

    /**
     * moves micromouse to desired coordinates
     * @param x x-axis coordinate
     * @param y y-axis coordinate
     */
    void move(int x, int y);

    /**
     * rotates micromouse to desired orientation
     * @param orientation orientation
     */
    void rotate(int orientation);

private:
    /// sensor used to determine if micromouse can move to specific location
    std::unique_ptr<MicromouseSensor> sensor;

    /// current position of micromouse
    QPoint pos;

    /// current orientation of micromouse, 0=North,1=East,2=South,3=West
    int orientation = 1;

    /// path recorded by micromouse
    MicromousePath path;
};


#endif //MICROMOUSE_H
