#include "Natives.h"
#include "pointers.h"
#include "Object.h"
#include "util.h"
#include "streamer.h"

//native PHY_InitObject(objectid, modelid = 0, Float:mass = 1.0, Float:size = FLOAT_NAN, mode = PHY_MODE_3D);
cell AMX_NATIVE_CALL Natives::PHY_InitObject(AMX* amx, cell* params)
{
    CHECK_PARAMS(5);

    int objectid, modelid, mode;
    float mass, size;

    objectid = (int) params[1];
    modelid = (int) params[2];
    mass = amx_ctof(params[3]);
    size = amx_ctof(params[4]);
    mode = (int) params[5];
    
    int id = g_Manager->addObject(Object(objectid, modelid, mass, size, mode));

    return id;
}

//native PHY_CreateWall(Float:x1, Float:y1, Float:x2, Float:y2, Float:constant = 1.0, Float:low = FLOAT_NEG_INFINITY, Float:high = FLOAT_INFINITY);
cell AMX_NATIVE_CALL Natives::PHY_CreateWall(AMX* amx, cell* params)
{
    CHECK_PARAMS(7);

    float x1, y1, x2, y2, constant, low, high;

    x1 = amx_ctof(params[1]);
    y1 = amx_ctof(params[2]);
    x2 = amx_ctof(params[3]);
    y2 = amx_ctof(params[4]);
    constant = amx_ctof(params[5]);
    low = amx_ctof(params[6]);
    high = amx_ctof(params[7]);

    int id = g_Manager->addWall(Wall(x1, y1, x2, y2, constant, low, high));

    return id;
}

//native PHY_DeleteObject(objectid);
cell AMX_NATIVE_CALL Natives::PHY_DeleteObject(AMX* amx, cell* params)
{
    CHECK_PARAMS(1);

    int objectid = (int) params[1];

    g_Manager->deleteItem(PHY_ITEM_OBJECT, objectid);
    return 1;
}

//native PHY_DestroyWall(wallid);
cell AMX_NATIVE_CALL Natives::PHY_DestroyWall(AMX* amx, cell* params)
{
    CHECK_PARAMS(1);

    int wallid = (int) params[1];

    g_Manager->deleteItem(PHY_ITEM_WALL, wallid);
    return 1;
}

//native PHY_SetObjectVelocity(objectid, Float:vx, Float:vy, Float:vz = 0.0);
cell AMX_NATIVE_CALL Natives::PHY_SetObjectVelocity(AMX* amx, cell* params)
{
    CHECK_PARAMS(4);

    int objectid;
    float vx, vy, vz;

    objectid = (int) params[1];
    vx = amx_ctof(params[2]);
    vy = amx_ctof(params[3]);
    vz = amx_ctof(params[4]);

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;

    object->m_VX = vx;
    object->m_VY = vy;
    object->m_VZ = vz;

    return 1;
}

//native PHY_GetObjectVelocity(objectid, &Float:vx, &Float:vy, &Float:vz);
cell AMX_NATIVE_CALL Natives::PHY_GetObjectVelocity(AMX* amx, cell* params)
{
    CHECK_PARAMS(4);

    int objectid = (int) params[1];

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;

    storeFloatInNative(amx, params[2], object->m_VX);
    storeFloatInNative(amx, params[3], object->m_VY);
    storeFloatInNative(amx, params[4], object->m_VZ);
    return 1;
}

//native PHY_GetHandleObject(handleid);
cell AMX_NATIVE_CALL Natives::PHY_GetHandleObject(AMX* amx, cell* params)
{
    CHECK_PARAMS(1);

    int objectid = (int) params[1];

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;

    return object->m_DynObject;
}

//native PHY_SetObjectFriction(objectid, Float:friction);
cell AMX_NATIVE_CALL Natives::PHY_SetObjectFriction(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int objectid;
    float friction;

    objectid = (int) params[1];
    friction = amx_ctof(params[2]);

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    if(friction < 0.0) return 0;

    object->m_Friction = friction;
    return 1;
}

//native PHY_RollObject(objectid, bool:toggle = true, rollingmode = PHY_ROLLING_MODE_DEFAULT);
cell AMX_NATIVE_CALL Natives::PHY_RollObject(AMX* amx, cell* params)
{
    CHECK_PARAMS(3);

    int objectid, toggle, rollingmode;

    objectid = (int) params[1];
    toggle = (int) params[2];
    rollingmode = (int) params[3];

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;

    object->toggleRolling(toggle, rollingmode);
    return 1;
}

//native PHY_SetWallWorld(wallid, world);
cell AMX_NATIVE_CALL Natives::PHY_SetWallWorld(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int wallid, worldid;

    wallid = (int) params[1];
    worldid = (int) params[2];

    auto wall = g_Manager->findWall(wallid);

    if(wall == nullptr) return 0;

    wall->setWorld(worldid);
    return 1;
}

//native PHY_SetObjectWorld(objectid, world);
cell AMX_NATIVE_CALL Natives::PHY_SetObjectWorld(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int objectid, worldid;

    objectid = (int) params[1];
    worldid = (int) params[2];

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    
    object->setWorld(worldid);
    return 1;
}

//native PHY_SetObjectAirResistance(objectid, Float:resistance);
cell AMX_NATIVE_CALL Natives::PHY_SetObjectAirResistance(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int objectid;
    float resistance;

    objectid = (int) params[1];
    resistance = amx_ctof(params[2]);

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    if(resistance < 0.0 || resistance > 1.0) return 0;
    
    object->m_AirResistance = resistance;
    return 1;
}

//native PHY_GetObjectMoveAngle(objectid, &Float:moveangle);
cell AMX_NATIVE_CALL Natives::PHY_GetObjectMoveAngle(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int objectid = (int) params[1];

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    
    storeFloatInNative(amx, params[2], object->getMoveAngle());
    return 1;
}

//native PHY_SetUpdateInterval(interval_ms);
cell AMX_NATIVE_CALL Natives::PHY_SetUpdateInterval(AMX* amx, cell* params)
{
    CHECK_PARAMS(1);

    int interval_ms = (int) params[1];

    g_Manager->setUpdateInterval(interval_ms);
    return 1;
}

//native PHY_CountItems(PHY_ITEM_TYPE:type);
cell AMX_NATIVE_CALL Natives::PHY_CountItems(AMX* amx, cell* params)
{
    CHECK_PARAMS(1);

    int type = (int) params[1];

    return g_Manager->countItems(type);
}

//native PHY_SetObjectZBound(objectid, Float:low = FLOAT_NAN, Float:high = FLOAT_NAN, Float:constant = 0.0);
cell AMX_NATIVE_CALL Natives::PHY_SetObjectZBound(AMX* amx, cell* params)
{
    CHECK_PARAMS(4);

    int objectid;
    float low, high, constant;

    objectid = (int) params[1];
    low = amx_ctof(params[2]);
    high = amx_ctof(params[3]);
    constant = amx_ctof(params[4]);

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    
    if(low == low)
        object->m_LowZBound = low;
    if(high == high)
        object->m_HighZBound = high;
    
    object->m_BoundConst = constant;
    return 1;
}

//native PHY_SetObjectGravity(objectid, Float:gravity);
cell AMX_NATIVE_CALL Natives::PHY_SetObjectGravity(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int objectid;
    float gravity;

    objectid = (int) params[1];
    gravity = amx_ctof(params[2]);

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    
    object->m_Gravity = gravity;
    return 1;
}

//native PHY_SetObjectAcceleration(objectid, Float:ax, Float:ay, Float:az = 0.0);
cell AMX_NATIVE_CALL Natives::PHY_SetObjectAcceleration(AMX* amx, cell* params)
{
    CHECK_PARAMS(4);

    int objectid;
    float ax, ay, az;

    objectid = (int) params[1];
    ax = amx_ctof(params[2]);
    ay = amx_ctof(params[3]);
    az = amx_ctof(params[4]);

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    
    object->m_AX = ax;
    object->m_AY = ay;
    object->m_AZ = az;
    return 1;
}

//native PHY_GetObjectAcceleration(objectid, &Float:ax, &Float:ay, &Float:az);
cell AMX_NATIVE_CALL Natives::PHY_GetObjectAcceleration(AMX* amx, cell* params)
{
    CHECK_PARAMS(4);

    int objectid = (int) params[1];

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;
    
    storeFloatInNative(amx, params[2], object->m_AX);
    storeFloatInNative(amx, params[3], object->m_AY);
    storeFloatInNative(amx, params[4], object->m_AZ);
    return 1;
}

//native PHY_ToggleObjectPlayerColls(objectid, toggle = 1, Float:constant = 1.0, Float:distoffset = 0.8, Float:zoffsetlow = 1.0, Float:zoffsethigh = 1.0);
cell AMX_NATIVE_CALL Natives::PHY_ToggleObjectPlayerColls(AMX* amx, cell* params)
{
    CHECK_PARAMS(6);

    int objectid = (int) params[1];
    int toggle = (int) params[2];
    float constant = amx_ctof(params[3]);
    float distoffset = amx_ctof(params[4]);
    float zoffsetlow = amx_ctof(params[5]);
    float zoffsethigh = amx_ctof(params[6]);

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;

    if(toggle)
    {
        object->m_Properties |= PHY_OBJECT_PLAYER_COLLISIONS;
        object->m_PlayerConst = constant;
        object->m_PlayerDist = distoffset;
        object->m_PlayerLowZ = zoffsetlow;
        object->m_PlayerHighZ = zoffsethigh;
    }
    else
    {
        object->m_Properties &= ~PHY_OBJECT_PLAYER_COLLISIONS;
    }
    return 1;
}

//native PHY_CreateCylinder(Float:x, Float:y, Float:size, Float:constant = 1.0, Float:low = FLOAT_NEG_INFINITY, Float:high = FLOAT_INFINITY);
cell AMX_NATIVE_CALL Natives::PHY_CreateCylinder(AMX* amx, cell* params)
{
    CHECK_PARAMS(6);

    float x = amx_ctof(params[1]);
    float y = amx_ctof(params[2]);
    float size = amx_ctof(params[3]);
    float constant = amx_ctof(params[4]);
    float low = amx_ctof(params[5]);
    float high = amx_ctof(params[6]);

    int id = g_Manager->addCylinder(Cylinder(x, y, size, constant, low, high));
    return id;
}

//native PHY_DestroyCylinder(cylinderid);
cell AMX_NATIVE_CALL Natives::PHY_DestroyCylinder(AMX* amx, cell* params)
{
    CHECK_PARAMS(1);

    int cylinderid = (int) params[1];

    g_Manager->deleteItem(PHY_ITEM_CYLINDER, cylinderid);
    return 1;
}

//native PHY_SetCylinderWorld(cylinderid, world);
cell AMX_NATIVE_CALL Natives::PHY_SetCylinderWorld(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int cylinderid = (int) params[1];
    int worldid = (int) params[2];

    auto cylinder = g_Manager->findCylinder(cylinderid);

    if(cylinder == nullptr) return 0;
    
    cylinder->setWorld(worldid);
    return 1;
}

//native PHY_GetObjectSpeed(objectid, &Float:speed, _3D = 0);
cell AMX_NATIVE_CALL Natives::PHY_GetObjectSpeed(AMX* amx, cell* params)
{
    CHECK_PARAMS(3);

    int objectid = (int) params[1];
    bool _3D = (bool) params[3];

    auto object = g_Manager->findObject(objectid);

    if(object == nullptr) return 0;

    storeFloatInNative(amx, params[2], object->getSpeed(_3D));
	return 1;
}

//native PHY_SetPlayerWorld(playerid, world);
cell AMX_NATIVE_CALL Natives::PHY_SetPlayerWorld(AMX* amx, cell* params)
{
    CHECK_PARAMS(2);

    int playerid = (int) params[1];
    int worldid = (int) params[2];

    auto player = g_Manager->findPlayer(playerid);

    if(player == nullptr) return 0;
    
    player->setWorld(worldid);
    return 1;
}