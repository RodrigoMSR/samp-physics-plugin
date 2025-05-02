#pragma once

namespace ColAndreas
{
    constexpr const int WATER_OBJECT = 20000;

    int RayCastLine(float StartX, float StartY, float StartZ, float EndX, float EndY, float EndZ, float& x, float& y, float& z);
    int RayCastLineAngle(float StartX, float StartY, float StartZ, float EndX, float EndY, float EndZ, float& x, float& y, float& z, float& rx, float& ry, float& rz);
    bool isLoaded();
}