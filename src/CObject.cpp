#include "CObject.h"
#include "util.h"
#include "streamer.h"
#include "model_sizes.h"

CObject::CObject(int objectid, int modelid, float mass, float size, int mode)
{
    float x, y, z;
    Streamer::GetDynamicObjectPos(objectid, x, y, z);

    m_Id = 0;
    m_Properties = PHY_OBJECT_USED | (mode ? PHY_OBJECT_MODE : 0);
    m_World = 0;
    m_DynObject = objectid;
    m_Mass = mass;
    m_VX = 0;
    m_VY = 0;
    m_VZ = 0;
    m_AX = 0;
    m_AY = 0;
    m_AZ = 0;
    m_AngularVelocity = 0;
    m_AxisX = 0;
    m_AxisY = 0;
    m_AxisZ = 0;
    m_QW = 0;
    m_QX = 0;
    m_QY = 0;
    m_QZ = 0;
    m_Friction = 0;
    m_AirResistance = 0;
    m_Gravity = 0;
    m_LowZBound = z;
    m_HighZBound = FLOAT_INFINITY;
    m_BoundConst = 0;
    m_PlayerConst = 0;
    m_PlayerDist = 0;
    m_PlayerLowZ = 0;
    m_PlayerHighZ = 0;
    
    if(size != size)
    {
        m_Size = ModelSizes::GetColSphereRadius(modelid);
    }
    else
    {
        m_Size = size;
    }
}

void CObject::setWorld(int world)
{
    m_World = world;
}

void CObject::applyRotation(float speed, float moveangle, int updateInterval)
{
	float rx, ry, rz;

	Streamer::GetDynamicObjectRot(m_DynObject, rx, ry, rz);

	rx -= speed * (updateInterval/1000.0) * (180.0/3.14159) / m_Size;

	if(rx < 0.0) rx += 360.0;

    rz = moveangle;
	
	Streamer::SetDynamicObjectRot(m_DynObject, rx, ry, rz);
}

/* New mode of rolling, based on Quaternions */
void CObject::applyQuaternionsRotation(float speed, float moveangle, int updateInterval)
{
	float rx, ry, rz, dx, dy, q_roll[4], vx, vy, vz, quat[4];
	
	dx = sin_degrees(-moveangle);
	dy = cos_degrees(-moveangle);

	PHY_vectorcrossp(dx, dy, 0.0, 0.0, 0.0, 1.0, vx, vy, vz);
	PHY_QuatFromAxisAngle(vx, vy, vz, (speed * (updateInterval/1000.0) * (180.0/3.14159)) / m_Size, q_roll[0], q_roll[1], q_roll[2], q_roll[3]);
	
	quat[0] = m_QW;
	quat[1] = m_QX;
	quat[2] = m_QY;
	quat[3] = m_QZ;

	PHY_GetQuatProduct(quat, q_roll, quat);
	
	m_QW = quat[0];
	m_QX = quat[1];
	m_QY = quat[2];
	m_QZ = quat[3];
	
	PHY_GetQuaternionAngles(quat[0], quat[1], quat[2], quat[3], rx, ry, rz);
	
	Streamer::SetDynamicObjectRot(m_DynObject, rx, ry, rz);
}

float CObject::getMoveAngle()
{
    return (atan2_degrees(m_VY, m_VX) - 90.0);
}

void CObject::toggleRolling(bool toggle, int rollingmode)
{
    if(toggle)
        m_Properties |= PHY_OBJECT_ROLL;
    else
        m_Properties &= ~PHY_OBJECT_ROLL;
    
    if(rollingmode == PHY_ROLLING_MODE_ADVANCED)
    {
        m_Properties |= PHY_OBJECT_ROLLING_MODE;
        
        float rx, ry, rz;
        Streamer::GetDynamicObjectRot(m_DynObject, rx, ry, rz);

        PHY_GetRotationQuaternion(rx, ry, rz, m_QW, m_QX, m_QY, m_QZ);
    }
    else
    {
        m_Properties &= ~PHY_OBJECT_ROLLING_MODE;
    }
}

bool CObject::isMoving()
{
    return (m_VX != 0 || m_VY != 0 || m_VZ != 0);
}

bool CObject::isUsing3D()
{
    return !(m_Properties & PHY_OBJECT_MODE);
}

bool CObject::isUsingColAndreasCollisions()
{
    return (m_Properties & PHY_OBJECT_COLANDREAS_COLLS);
}

bool CObject::isUsingColAndreasBounds()
{
    return (m_Properties & PHY_OBJECT_COLANDREAS_BOUNDS);
}

bool CObject::isGhostWithObjects()
{
    return (m_Properties & PHY_OBJECT_GHOST_OBJECTS);
}

bool CObject::isGhostWithWalls()
{
    return (m_Properties & PHY_OBJECT_GHOST_WALLS);
}

bool CObject::isGhostWithCylinders()
{
    return (m_Properties & PHY_OBJECT_GHOST_CYLINDERS);
}

bool CObject::isCollidingWithPlayers()
{
    return (m_Properties & PHY_OBJECT_PLAYER_COLLISIONS);
}

bool CObject::isRolling()
{
    return (m_Properties & PHY_OBJECT_ROLL);
}

bool CObject::isRollingModeAdvanced()
{
    return (m_Properties & PHY_OBJECT_ROLLING_MODE);
}