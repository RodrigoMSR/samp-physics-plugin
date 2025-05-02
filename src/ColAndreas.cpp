#include "ColAndreas.hpp"
#include <sampgdk.h>

int ColAndreas::RayCastLine(float StartX, float StartY, float StartZ, float EndX, float EndY, float EndZ, float& x, float& y, float& z)
{
    AMX_NATIVE native = sampgdk::FindNative("CA_RayCastLine");
    cell cx, cy, cz, ret;
    
    if(native == NULL) return 0;

    ret = sampgdk::InvokeNative(native, "ffffffRRR", StartX, StartY, StartZ, EndX, EndY, EndZ, &cx, &cy, &cz);

    x = amx_ctof(cx);
    y = amx_ctof(cy);
    z = amx_ctof(cz);
    return ret;
}

int ColAndreas::RayCastLineAngle(float StartX, float StartY, float StartZ, float EndX, float EndY, float EndZ, float& x, float& y, float& z, float& rx, float& ry, float& rz)
{
    AMX_NATIVE native = sampgdk::FindNative("CA_RayCastLineAngle");
    cell cx, cy, cz, crx, cry, crz, ret;
    
    if(native == NULL) return 0;

    ret = sampgdk::InvokeNative(native, "ffffffRRRRRR", StartX, StartY, StartZ, EndX, EndY, EndZ, &cx, &cy, &cz, &crx, &cry, &crz);

    x = amx_ctof(cx);
    y = amx_ctof(cy);
    z = amx_ctof(cz);

    rx = amx_ctof(crx);
    ry = amx_ctof(cry);
    rz = amx_ctof(crz);

    return ret;
}

bool ColAndreas::isLoaded()
{
    AMX_NATIVE native = sampgdk::FindNative("CA_RayCastLine");

    return (native != NULL);
}