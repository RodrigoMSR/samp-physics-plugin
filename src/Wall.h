#pragma once

class Wall
{
public:
    int m_Id;
    int m_World;
    float m_X1;
    float m_Y1;
    float m_X2;
    float m_Y2;
    float m_Z1;
    float m_Z2;
    float m_BounceConst;
    float m_ANG;

    Wall(float x1, float y1, float x2, float y2, float constant, float low, float high);
    void setWorld(int world);
};