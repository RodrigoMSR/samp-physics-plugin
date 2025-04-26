#include "Cylinder.hpp"

Cylinder::Cylinder(float x, float y, float size, float constant, float low, float high)
{
    m_Id = 0;
    m_World = 0;
    m_X = x;
    m_Y = y;
    m_Size = size;
    m_Z1 = low;
    m_Z2 = high;
    m_BounceConst = constant;
}

void Cylinder::setWorld(int world)
{
    m_World = world;
}