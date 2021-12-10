#pragma once

#include <cmath>

namespace Chinar::Math {

    constexpr float Pi = 3.1415926535f;
    constexpr float TwoPi = Pi * 2.0f;
    constexpr float PiOver2 = Pi / 2.0f;
    
    inline float toDegree(const float rad) {
        return rad * 180.0f / Pi;
    }

    inline float toReadians(const float deg) {
        return deg * Pi / 180.0f;
    } 

    inline bool nearZero(float val, float epsilon = 0.001f) {
        return std::fabs(val) <= epsilon;
    }
}
