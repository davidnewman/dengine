#include "Motion.h"

using namespace dengine;

Motion::Motion() :
    Motion(Vector2d{0.0, 0.0}, Vector2d{0.0, 0.0}, Vector2d{0.0, 0.0}) {}

Motion::Motion(Vector2d d) :
    Motion(d, Vector2d{0.0, 0.0}, Vector2d{0.0, 0.0}) {}

Motion::Motion(Vector2d d, Vector2d v) :
    Motion(d, v, Vector2d{0.0, 0.0}) {}

Motion::Motion(Vector2d d, Vector2d v, Vector2d a) :
    disp{d}, vel{v}, accel{a} {}

void Motion::accelerate(Vector2d a) {
    accel = a;
}

void Motion::displace(Vector2d d) {
    disp += d;
}

Vector2d Motion::displacement() const {
    return disp;
}

Vector2d Motion::velocity() const {
    return vel;
}


Vector2d Motion::acceleration() const {
    return accel;
}

Vector2d Motion::move(double t) {
    vel = vel + (accel * t);
    auto delta_v = (vel * t) + ((accel * 0.5) * (t * t));
    disp += delta_v;

    return disp;
}

void Motion::stop() {
    vel = Vector2d{0.0, 0.0};
    accel = Vector2d{0.0, 0.0};
}
