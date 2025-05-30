#include "Object.hpp"
#include "Util.hpp"
#include "Streamer.hpp"
#include "ModelSizes.hpp"
#include "ColAndreas.hpp"
#include <cmath>

Object::Object(int objectid, int modelid, float mass, float size, int mode)
{
    float x, y, z;
    Streamer::GetDynamicObjectPos(objectid, x, y, z);

    m_Id = objectid;
    m_Properties = PHY_OBJECT_USED | (mode ? PHY_OBJECT_MODE : 0);
    m_World = 0;
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

void Object::setWorld(int world)
{
    m_World = world;
}

void Object::applyRotation(float speed, float moveangle, int updateInterval)
{
	float rx, ry, rz;

	Streamer::GetDynamicObjectRot(m_Id, rx, ry, rz);

	rx -= speed * (updateInterval/1000.0) * (180.0/3.14159) / m_Size;

	if(rx < 0.0) rx += 360.0;

    rz = moveangle;
	
	Streamer::SetDynamicObjectRot(m_Id, rx, ry, rz);
}

/* New mode of rolling, based on Quaternions */
void Object::applyQuaternionsRotation(float speed, float moveangle, int updateInterval)
{
	float rx, ry, rz, dx, dy, q_roll[4], vx, vy, vz, quat[4];
	
	dx = Util::sin_degrees(-moveangle);
	dy = Util::cos_degrees(-moveangle);

	Util::vectorcrossp(dx, dy, 0.0, 0.0, 0.0, 1.0, vx, vy, vz);
	Util::quatFromAxisAngle(vx, vy, vz, (speed * (updateInterval/1000.0) * (180.0/3.14159)) / m_Size, q_roll[0], q_roll[1], q_roll[2], q_roll[3]);
	
	quat[0] = m_QW;
	quat[1] = m_QX;
	quat[2] = m_QY;
	quat[3] = m_QZ;

	Util::getQuatProduct(quat, q_roll, quat);
	
	m_QW = quat[0];
	m_QX = quat[1];
	m_QY = quat[2];
	m_QZ = quat[3];
	
	Util::getQuaternionAngles(quat[0], quat[1], quat[2], quat[3], rx, ry, rz);
	
	Streamer::SetDynamicObjectRot(m_Id, rx, ry, rz);
}

float Object::getMoveAngle()
{
    return (Util::atan2_degrees(m_VY, m_VX) - 90.0);
}

void Object::toggleRolling(bool toggle, int rollingmode)
{
    if(toggle)
        m_Properties |= PHY_OBJECT_ROLL;
    else
        m_Properties &= ~PHY_OBJECT_ROLL;
    
    if(rollingmode == PHY_ROLLING_MODE_ADVANCED)
    {
        m_Properties |= PHY_OBJECT_ROLLING_MODE;
        
        float rx, ry, rz;
        Streamer::GetDynamicObjectRot(m_Id, rx, ry, rz);

        Util::getRotationQuaternion(rx, ry, rz, m_QW, m_QX, m_QY, m_QZ);
    }
    else
    {
        m_Properties &= ~PHY_OBJECT_ROLLING_MODE;
    }
}

bool Object::isMoving()
{
    return (m_VX != 0 || m_VY != 0 || m_VZ != 0);
}

bool Object::isUsing3D()
{
    return !(m_Properties & PHY_OBJECT_MODE);
}

bool Object::isUsingColAndreasCollisions()
{
    return (m_Properties & PHY_OBJECT_COLANDREAS_COLLS);
}

bool Object::isUsingColAndreasBounds()
{
    return (m_Properties & PHY_OBJECT_COLANDREAS_BOUNDS);
}

bool Object::isGhostWithObjects()
{
    return (m_Properties & PHY_OBJECT_GHOST_OBJECTS);
}

bool Object::isGhostWithWalls()
{
    return (m_Properties & PHY_OBJECT_GHOST_WALLS);
}

bool Object::isGhostWithCylinders()
{
    return (m_Properties & PHY_OBJECT_GHOST_CYLINDERS);
}

bool Object::isCollidingWithPlayers()
{
    return (m_Properties & PHY_OBJECT_PLAYER_COLLISIONS);
}

bool Object::isRolling()
{
    return (m_Properties & PHY_OBJECT_ROLL);
}

bool Object::isRollingModeAdvanced()
{
    return (m_Properties & PHY_OBJECT_ROLLING_MODE);
}

float Object::getSpeed(bool _3D)
{
    return sqrt(
		m_VX * m_VX +
		m_VY * m_VY +
		_3D ? (m_VZ * m_VZ) : 0.0
	);
}

int Object::useColAndreas(int mode)
{
    if(!ColAndreas::isLoaded()) return 0;

    float x, y, z;
    Streamer::GetDynamicObjectPos(m_Id, x, y, z);

    switch(mode)
    {
        case PHY_CA_NONE:
        {
            m_Properties &= ~PHY_OBJECT_COLANDREAS_BOUNDS;
            m_Properties &= ~PHY_OBJECT_COLANDREAS_COLLS;
            break;
        }
        case PHY_CA_FULL:
        {
            m_Properties |= PHY_OBJECT_COLANDREAS_BOUNDS;
            m_Properties |= PHY_OBJECT_COLANDREAS_COLLS;
            updateCABounds(x, y, z);
            break;
        }
        case PHY_CA_COLLS:
        {
            m_Properties &= ~PHY_OBJECT_COLANDREAS_BOUNDS;
            m_Properties |= PHY_OBJECT_COLANDREAS_COLLS;
            break;
        }
        case PHY_CA_BOUNDS:
        {
            m_Properties |= PHY_OBJECT_COLANDREAS_BOUNDS;
            m_Properties &= ~PHY_OBJECT_COLANDREAS_COLLS;
            updateCABounds(x, y, z);
            break;
        }
    }
    return 1;
}

void Object::updateCABounds(float x, float y, float z)
{
	float unused, bound;
    int collModel;
	
	collModel = ColAndreas::RayCastLine(x, y, z, x, y, z - 1000.0, unused, unused, bound);

	if(collModel != 0)
    {
        if(collModel != ColAndreas::WATER_OBJECT)
        {
            m_LowZBound = bound + m_Size;
        }
        else
        {
            m_LowZBound = bound - 0.1;
        }
    }

    collModel = ColAndreas::RayCastLine(x, y, z, x, y, z + 1000.0, unused, unused, bound);
	
    if(collModel != 0 && collModel != ColAndreas::WATER_OBJECT && bound > m_LowZBound)
		m_HighZBound = bound - m_Size;
	else
		m_HighZBound = FLOAT_INFINITY;
}