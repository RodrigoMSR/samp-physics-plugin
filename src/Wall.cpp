#include "Wall.hpp"
#include "util.hpp"

Wall::Wall(float x1, float y1, float x2, float y2, float constant, float low, float high)
{
    m_Id = 0;
    m_World = 0;
    m_X1 = x1;
    m_Y1 = y1;
    m_X2 = x2;
    m_Y2 = y2;
    m_Z1 = low;
    m_Z2 = high;
    m_BounceConst = constant;
    m_ANG = Util::atan2_degrees(y1 - y2, x1 - x2);
}

void Wall::setWorld(int world)
{
    m_World = world;
}