#include "Vector2d.h"

using namespace dengine;

double Vector2d::magnitude() const {
    if (!isnan(_mag)) {
        return _mag;
    }

    _mag = sqrt(pow(_x, 2) + pow(_y, 2));

    return _mag;
}

double Vector2d::theta() const {
    if (!isnan(_theta)) {
        return _theta;
    }

    auto t = atan(_y / _x);

    // Correct the radians based on what
    // quadrant the x,y coordinate is in.
    if ((_x < 0 && _y > 0) ||
        (_x < 0 && _y < 0)) {
        // NW, SW quadrant
        t = t + M_PI;
    } else if (_y < 0) {
        // SE quadrant
        t = t + (2.0 * M_PI);
    }

    _theta = t;

    return _theta;
}

Vector2d Vector2d::magnitude_direction(double mag, double theta) {
    double x{mag * cos(theta)};
    double y{mag * sin(theta)};

    Vector2d v{x, y};
    v._mag = mag;
    v._theta = theta;

    return v;
}
