#pragma once

#include "defines.h"

class Object
{
public:
    int m_Id;
    int m_Properties;
    int m_World;
    int m_DynObject;
    float m_Size;
    float m_Mass;
    float m_VX;
    float m_VY;
    float m_VZ;
    float m_AX;
    float m_AY;
    float m_AZ;
    float m_AngularVelocity;
    float m_AxisX;
    float m_AxisY;
    float m_AxisZ;
    float m_QW;
    float m_QX;
    float m_QY;
    float m_QZ;
    float m_Friction;
    float m_AirResistance;
    float m_Gravity;
    float m_LowZBound;
    float m_HighZBound;
    float m_BoundConst;
    float m_PlayerConst;
    float m_PlayerDist;
    float m_PlayerLowZ;
    float m_PlayerHighZ;

    Object();
    Object(int objectid, int modelid, float mass, float size, int mode);
    void setWorld(int world);
    void applyRotation(float speed, float moveangle, int updateInterval);
    void applyQuaternionsRotation(float speed, float moveangle, int updateInterval);
    float getMoveAngle();
    void toggleRolling(bool toggle, int rollingmode);
    bool isMoving();
    bool isUsing3D();
    bool isUsingColAndreasCollisions();
    bool isUsingColAndreasBounds();
    bool isGhostWithObjects();
    bool isGhostWithWalls();
    bool isGhostWithCylinders();
    bool isCollidingWithPlayers();
    bool isRolling();
    bool isRollingModeAdvanced();
    float getSpeed(bool _3D = true);
};