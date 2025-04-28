#include "Streamer.hpp"
#include <sampgdk.h>

int Streamer::GetDynamicObjectRot(int objectid, float& rx, float& ry, float& rz)
{
    AMX_NATIVE native = sampgdk::FindNative("GetDynamicObjectRot");
    cell cx, cy, cz, ret;
    
    if(native == NULL) return 0;

    ret = sampgdk::InvokeNative(native, "dRRR", objectid, &cx, &cy, &cz);

    rx = amx_ctof(cx);
    ry = amx_ctof(cy);
    rz = amx_ctof(cz);
    return ret;
}

int Streamer::GetDynamicObjectPos(int objectid, float& x, float& y, float& z)
{
    AMX_NATIVE native = sampgdk::FindNative("GetDynamicObjectPos");
    cell cx, cy, cz, ret;

    if(native == NULL) return 0;

    ret = sampgdk::InvokeNative(native, "dRRR", objectid, &cx, &cy, &cz);

    x = amx_ctof(cx);
    y = amx_ctof(cy);
    z = amx_ctof(cz);
    return ret;
}

void Streamer::SetDynamicObjectPos(int objectid, float& x, float& y, float& z)
{
    AMX_NATIVE native = sampgdk::FindNative("SetDynamicObjectPos");
    
    if(native == NULL) return;

    sampgdk::InvokeNative(native, "dfff", objectid, x, y, z);
}

void Streamer::SetDynamicObjectRot(int objectid, float& rx, float& ry, float& rz)
{
    AMX_NATIVE native = sampgdk::FindNative("SetDynamicObjectRot");
    
    if(native == NULL) return;

    sampgdk::InvokeNative(native, "dfff", objectid, rx, ry, rz);
}