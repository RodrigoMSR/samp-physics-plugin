#pragma once

namespace Streamer
{
    int GetDynamicObjectRot(int objectid, float& rx, float& ry, float& rz);
    int GetDynamicObjectPos(int objectid, float& x, float& y, float& z);
    void SetDynamicObjectPos(int objectid, float& x, float& y, float& z);
    void SetDynamicObjectRot(int objectid, float& rx, float& ry, float& rz);
    int IsValidDynamicObject(int objectid);
}