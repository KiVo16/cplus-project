#include "Micromouse.h"

#include <iostream>
#include <ostream>

#include "Sensor/MicromouseSensor.h"

Micromouse::Micromouse(std::unique_ptr<MicromouseSensor> sensor, const QPoint start): sensor(std::move(sensor)), pos(start) {
}

QPoint Micromouse::getCurrentPosition() const {
    return pos;
}

int Micromouse::getCurrentOrientation() const {
    return orientation;
}

MicromousePath Micromouse::getPath() const {
    return path;
}

const std::unique_ptr<MicromouseSensor> &Micromouse::getSensor() const {
    return sensor;
}

void Micromouse::move(int x, int y) {
    pos = QPoint(x, y);
    path.push_back({
        pos,
        orientation,
    });
}

void Micromouse::rotate(int orientation) {
    this->orientation = orientation;
    path.push_back({
        pos,
        orientation,
    });
}