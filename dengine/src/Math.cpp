#include "DMath.h"

using namespace dengine;

double dengine::radians(double degrees) {
    return degrees * _pi_over_180;
}

double dengine::degrees(double radians) {
    return radians * _180_over_pi;
}
