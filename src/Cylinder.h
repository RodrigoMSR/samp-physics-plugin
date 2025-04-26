#pragma once

class Cylinder
{
public:
    int m_Id;
    int m_World;
    float m_X;
    float m_Y;
    float m_Z1;
    float m_Z2;
    float m_Size;
    float m_BounceConst;

    Cylinder(float x, float y, float size, float constant, float low, float high);
    void setWorld(int world);
};