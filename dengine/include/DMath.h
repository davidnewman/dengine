#ifndef _DENGINE_MATH_INCL
#define _DENGINE_MATH_INCL

#include <cmath>
#include "Vector2d.h"

namespace dengine {
    constexpr double _180_over_pi = (180.0 / M_PI);
    constexpr double _pi_over_180 = (M_PI / 180.0);

    double radians(double degrees);
    double degrees(double radians);
}
#endif
