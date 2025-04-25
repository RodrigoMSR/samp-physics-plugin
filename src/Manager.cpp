#include "Manager.h"
#include "util.h"
#include "Callbacks.h"
#include "streamer.h"
#include <cmath>

int Manager::addObject(CObject object)
{
    int id = m_Identifier[PHY_ITEM_OBJECT].get();

    object.m_Id = id;

    m_Objects.insert(std::make_pair(id, std::shared_ptr<CObject>(new CObject(object))));
    return id;
}

int Manager::addWall(Wall wall)
{
    int id = m_Identifier[PHY_ITEM_WALL].get();

    wall.m_Id = id;

    m_Walls.insert(std::make_pair(id, std::shared_ptr<Wall>(new Wall(wall))));
    return id;
}

void Manager::deleteObject(int id)
{
    m_RemoveObjects.insert(id);
    //m_Objects.erase(id);
}

void Manager::deleteWall(int id)
{
    m_RemoveWalls.insert(id);
    //m_Walls.erase(id);
}

std::shared_ptr<CObject> Manager::findObject(int id)
{
    auto it = m_Objects.find(id);

    if(it == m_Objects.end()) return nullptr;
    
    return it->second;
}

std::shared_ptr<Wall> Manager::findWall(int id)
{
    auto it = m_Walls.find(id);

    if(it == m_Walls.end()) return nullptr;
    
    return it->second;
}

void Manager::setUpdateInterval(int interval_ms)
{
    if(interval_ms < 0) return;
    
    m_UpdateInterval = interval_ms;
}

bool Manager::shouldUpdate()
{
    auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_LastUpdate);

    int d = diff.count() - m_UpdateInterval;

    if(d + m_LastDelayMs < 0) return false;

    m_LastDelayMs += d;
    
    if(m_LastDelayMs < 0 || m_LastDelayMs > m_UpdateInterval * 3)
        m_LastDelayMs = 0;

    m_LastUpdate = now;
    return true;
}

void Manager::removeMarkedItems()
{
    for(auto id : m_RemoveObjects)
    {
        if(m_Objects.erase(id))
            m_Identifier[PHY_ITEM_OBJECT].remove(id, m_Objects.size());
    }

    for(auto id : m_RemoveWalls)
    {
        if(m_Walls.erase(id))
            m_Identifier[PHY_ITEM_WALL].remove(id, m_Walls.size());
    }

    m_RemoveObjects.clear();
    m_RemoveWalls.clear();
}

int Manager::countItems(int type)
{
    switch(type)
    {
        case PHY_ITEM_OBJECT:
            return m_Objects.size();
        case PHY_ITEM_WALL:
            return m_Walls.size();
    }
    return 0;
}

void Manager::update()
{
    float x, y, z;
    float x1, y1, z1;
    float xclosest, yclosest;
    float x2, y2, z2;
    float speed;
    float dx, dy, dz;
    float dist;
    float maxdist;
    float angle;
    float moveangle;
    float dvx, dvy, dvz;
    float mag;
    float tmpvx, tmpvy, tmpvz;
    float newvy1, newvy2, newvx1, newvx2, newvz1, newvz2;

    float timeMultiplier = (m_UpdateInterval / 1000.0);
    
    removeMarkedItems();

	for(auto& a_it : m_Objects)
	{
        auto a = a_it.second;

        Streamer::GetDynamicObjectPos(a->m_DynObject, x, y, z);
        
        x1 = x + a->m_VX * timeMultiplier;
        y1 = y + a->m_VY * timeMultiplier;
        
        if(a->isUsing3D())
        {
            z1 = z + a->m_VZ * timeMultiplier;
            
            if(z1 > a->m_HighZBound)
            {
                if(a->m_VZ > 0)
                {
                    a->m_VZ = -a->m_VZ * a->m_BoundConst;
                    //CallLocalFunction("PHY_OnObjectCollideWithZBound", "dd", a, 1);
                }
                z1 = a->m_HighZBound;
            }
            else if(z1 < a->m_LowZBound)
            {
                if(a->m_VZ < 0)
                {
                    a->m_VZ = -a->m_VZ * a->m_BoundConst;
                    //CallLocalFunction("PHY_OnObjectCollideWithZBound", "dd", a, 0);
                }
                z1 = a->m_LowZBound;
            }
            
            if(a->m_Gravity != 0)
            {
                if(a->m_VZ > 0)
                {
                    a->m_VZ -= a->m_Gravity * timeMultiplier;
                    if(a->m_VZ < 0)
                        a->m_VZ = 0;
                }
                else if(z1 > a->m_LowZBound)
                    a->m_VZ -= a->m_Gravity * timeMultiplier;
            }
        }
        else
            z1 = z;
        
        if(a->isMoving())
        {
            if(!a->isGhostWithObjects())
            {
                for(auto& b_it : m_Objects)
                {
                    auto b = b_it.second;

                    if(a->m_Id != b->m_Id && !b->isGhostWithObjects() && (!a->m_World || !b->m_World || a->m_World == b->m_World))
                    {
                        Streamer::GetDynamicObjectPos(b->m_DynObject, x2, y2, z2);

                        dx = x1 - x2;
                        dy = y1 - y2;
                        dz = (a->isUsing3D() && b->isUsing3D()) ? (z1 - z2) : (0.0);
                        
                        dist = (dx * dx) + (dy * dy) + (dz * dz);
                        maxdist = a->m_Size + b->m_Size;
                        
                        if(dist < (maxdist * maxdist))
                        {
                            dvx = a->m_VX - b->m_VX;
                            dvy = a->m_VY - b->m_VY;
                            dvz = a->m_VZ - b->m_VZ;
                            mag = dvx * dx + dvy * dy + dvz * dz;

                            if(mag < 0.0)
                            {
                                newvx1 = a->m_VX;
                                newvy1 = a->m_VY;
                                newvz1 = a->m_VZ;
                                newvx2 = b->m_VX;
                                newvy2 = b->m_VY;
                                newvz2 = b->m_VZ;

                                projectVonU(a->m_VX, a->m_VY, a->m_VZ, dx, dy, dz, tmpvx, tmpvy, tmpvz);
                                newvx1 -= tmpvx;
                                newvy1 -= tmpvy;
                                newvz1 -= tmpvz;
                                projectVonU(b->m_VX, b->m_VY, b->m_VZ, -dx, -dy, -dz, tmpvx, tmpvy, tmpvz);
                                tmpvx = ((a->m_Mass - b->m_Mass) * a->m_VX + 2 * b->m_Mass * tmpvx) / (a->m_Mass + b->m_Mass);
                                tmpvy = ((a->m_Mass - b->m_Mass) * a->m_VY + 2 * b->m_Mass * tmpvy) / (a->m_Mass + b->m_Mass);
                                tmpvz = ((a->m_Mass - b->m_Mass) * a->m_VZ + 2 * b->m_Mass * tmpvz) / (a->m_Mass + b->m_Mass);
                                newvx1 += tmpvx;
                                newvy1 += tmpvy;
                                newvz1 += tmpvz;

                                projectVonU(b->m_VX, b->m_VY, b->m_VZ, dx, dy, dz, tmpvx, tmpvy, tmpvz);
                                newvx2 -= tmpvx;
                                newvy2 -= tmpvy;
                                newvz2 -= tmpvz;
                                projectVonU(a->m_VX, a->m_VY, a->m_VZ, -dx, -dy, -dz, tmpvx, tmpvy, tmpvz);
                                tmpvx = ((b->m_Mass - a->m_Mass) * b->m_VX + 2 * a->m_Mass * tmpvx) / (a->m_Mass + b->m_Mass);
                                tmpvy = ((b->m_Mass - a->m_Mass) * b->m_VY + 2 * a->m_Mass * tmpvy) / (a->m_Mass + b->m_Mass);
                                tmpvz = ((b->m_Mass - a->m_Mass) * b->m_VZ + 2 * a->m_Mass * tmpvz) / (a->m_Mass + b->m_Mass);
                                newvx2 += tmpvx;
                                newvy2 += tmpvy;
                                newvz2 += tmpvz;

                                a->m_VX = newvx1;
                                a->m_VY = newvy1;
                                a->m_VZ = newvz1;

                                b->m_VX = newvx2;
                                b->m_VY = newvy2;
                                b->m_VZ = newvz2;

                                Callbacks::OnObjectCollideWithObject(a->m_Id, b->m_Id);
                            }
                        }
                    }
                }
            }
            
            if(!a->isGhostWithWalls())
            {
                for(auto& w_it : m_Walls)
                {
                    auto w = w_it.second;

                    if((!a->m_World || !w->m_World || a->m_World == w->m_World))
                    {
                        angle = w->m_ANG;
                        if(z1 < w->m_Z2 + a->m_Size && z1 > w->m_Z1 - a->m_Size + a->m_Size &&
                        (check_segment_intersection(w->m_X1, w->m_Y1, w->m_X2, w->m_Y2, x1, y1, a->m_Size, xclosest, yclosest) ||
                        check_segment_intersection(w->m_X1, w->m_Y1, w->m_X2, w->m_Y2, (x + x1)/2, (y + y1)/2, a->m_Size, xclosest, yclosest)))
                        {
                            newvx1 = w->m_BounceConst * (a->m_VX * cos_degrees(angle) - a->m_VY * sin_degrees(angle));
                            newvy1 = -w->m_BounceConst * (a->m_VX * sin_degrees(angle) + a->m_VY * cos_degrees(angle));
                            angle = -angle;
                            a->m_VX = newvx1 * cos_degrees(angle) - newvy1 * sin_degrees(angle);
                            a->m_VY = newvx1 * sin_degrees(angle) + newvy1 * cos_degrees(angle);

                            angle = angle + (newvy1 > 0 ? 90.0 : -90.0);
                            x1 = xclosest + (a->m_Size + 0.001) * cos_degrees(angle);
                            y1 = yclosest + (a->m_Size + 0.001) * sin_degrees(angle);

                            Callbacks::OnObjectCollideWithWall(a->m_Id, w->m_Id);
                        }
                    }
                }
            }

            /*
            if(!a->isGhostWithCylinders())
            {
                foreach(new c : ITER_Cylinder)
                {
                    if((!a->m_World || !c.m_World || a->m_World == c.m_World))
                    {
                        if(c.m_Z1 - a->m_Size < z1 < c.m_Z2 + a->m_Size)
                        {
                            x2 = c.PHY_X;
                            y2 = c.PHY_Y;
                            dx = x1 - x2;
                            dy = y1 - y2;
                            dist = (dx * dx) + (dy * dy);
                            maxdist = a->m_Size + c.m_Size;
                            if(dist < (maxdist * maxdist))
                            {
                                mag = a->m_VX * dx + a->m_VY * dy;

                                if(mag < 0.0)
                                {
                                    angle = -atan2_degrees(dy, dx);
                                    newvx1 = -c.m_BounceConst * (a->m_VX * cos_degrees(angle) - a->m_VY * sin_degrees(angle));
                                    newvy1 = c.m_BounceConst * (a->m_VX * sin_degrees(angle) + a->m_VY * cos_degrees(angle));

                                    angle = -angle;
                                    a->m_VX = newvx1 * cos_degrees(angle) - newvy1 * sin_degrees(angle);
                                    a->m_VY = newvx1 * sin_degrees(angle) + newvy1 * cos_degrees(angle);

                                    CallLocalFunction("PHY_OnObjectCollideWithCylinder", "dd", a, c);
                                }
                            }
                        }
                    }
                }
            }

            if(a->isCollidingWithPlayers())
            {
                foreach(new i : Player)
                {
                    if((!a->m_World || !PHY_Player[i][m_World] || a->m_World == PHY_Player[i][m_World]))
                    {
                        GetPlayerPos(i, x2, y2, z2);
                            
                        if(z2 - a->m_PlayerLowZ - a->m_Size < z1 < z2 + a->m_PlayerHighZ + a->m_Size)
                        {
                            dx = x1 - x2;
                            dy = y1 - y2;
                            dist = (dx * dx) + (dy * dy);
                            maxdist = a->m_Size + a->m_PlayerDist;
                            if(dist < (maxdist * maxdist))
                            {
                                mag = a->m_VX * dx + a->m_VY * dy;

                                if(mag < 0.0)
                                {
                                    angle = -atan2_degrees(dy, dx);
                                    newvx1 = -a->m_PlayerConst * (a->m_VX * cos_degrees(angle) - a->m_VY * sin_degrees(angle));
                                    newvy1 = a->m_PlayerConst * (a->m_VX * sin_degrees(angle) + a->m_VY * cos_degrees(angle));

                                    angle = -angle;
                                    a->m_VX = newvx1 * cos_degrees(angle) - newvy1 * sin_degrees(angle);
                                    a->m_VY = newvx1 * sin_degrees(angle) + newvy1 * cos_degrees(angle);

                                    CallLocalFunction("PHY_OnObjectCollideWithPlayer", "dd", a, i);
                                }
                            }
                        }
                    }
                }
            }
            */
            
            moveangle = atan2_degrees(a->m_VY, a->m_VX) - 90.0;
            speed = sqrt(a->m_VX * a->m_VX + a->m_VY * a->m_VY);

            if(a->m_Friction != 0 && z1 == a->m_LowZBound)
            {
                speed -= a->m_Friction * timeMultiplier;

                if(speed < 0.001)
                    speed = 0;
                
                a->m_VX = speed * sin_degrees(-moveangle);
                a->m_VY = speed * cos_degrees(-moveangle);
            }

            if(a->m_AirResistance != 0)
            {
                a->m_VX -= a->m_VX * a->m_AirResistance * timeMultiplier;
                a->m_VY -= a->m_VY * a->m_AirResistance * timeMultiplier;
                a->m_VZ -= a->m_VZ * a->m_AirResistance * timeMultiplier;
            }

            if(a->isRolling() && speed > 0.0)
            {
                if(a->isRollingModeAdvanced())
                    a->applyQuaternionsRotation(speed, moveangle, m_UpdateInterval);
                else
                    a->applyRotation(speed, moveangle, m_UpdateInterval);
            }
        }
        
        a->m_VX += a->m_AX;
        a->m_VY += a->m_AY;
        a->m_VZ += a->m_AZ;
        
        if(x1 != x || y1 != y || z1 != z)
        {
            Streamer::SetDynamicObjectPos(a->m_DynObject, x1, y1, z1);
            Callbacks::OnObjectUpdate(a->m_Id);
        }
    }
}