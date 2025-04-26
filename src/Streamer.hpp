#pragma once

namespace Streamer
{
    void GetDynamicObjectRot(int objectid, float& rx, float& ry, float& rz);
    void GetDynamicObjectPos(int objectid, float& x, float& y, float& z);
    void SetDynamicObjectPos(int objectid, float& x, float& y, float& z);
    void SetDynamicObjectRot(int objectid, float& rx, float& ry, float& rz);
}