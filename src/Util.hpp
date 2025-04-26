#pragma once

#include <sampgdk.h>

namespace Util
{
    float vectordotp(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z);
    void projectVonU(float vx, float vy, float vz, float ux, float uy, float uz, float& x, float& y, float& z);
    bool check_segment_intersection(float x1, float y1, float x2, float y2, float xc, float yc, float r, float& x, float& y);
    void vectorcrossp(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float& c1, float& c2, float& c3);
    void quatFromAxisAngle(float x, float y, float z, float angle, float& q_w, float& q_x, float& q_y, float& q_z);
    void quatNormalize(float& q_w, float& q_x, float& q_y, float& q_z);
    float asin_limit(float value);
    float atan2_limit(float x, float y);
    void getQuatProduct(const float q1[4], const float q2[4], float q3[4]);
    void getQuaternionAngles(float w, float x, float y, float z, float& xa, float& ya, float& za);
    void getRotationQuaternion(float x, float y, float z, float& qw, float& qx, float& qy, float& qz);
    double sin_degrees(double degrees);
    double cos_degrees(double degrees);
    double atan2_degrees(double y, double x);
    void storeFloatInNative(AMX *amx, cell output, float value);
    void storeIntegerInNative(AMX *amx, cell output, int value);
    double asin_degrees(double x);
}