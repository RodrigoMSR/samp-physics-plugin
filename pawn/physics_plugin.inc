#if defined _physics_included
	#endinput
#endif
#define _physics_included

#if !defined _streamer_included
	#error You must include streamer.inc before physics.inc
#endif

// Definitions

#define PHY_MODE_3D (0)
#define PHY_MODE_2D (1)

#define PHY_ROLLING_MODE_DEFAULT (0)
#define PHY_ROLLING_MODE_ADVANCED (1)

enum
{
	PHY_ITEM_OBJECT,
	PHY_ITEM_WALL,
    PHY_ITEM_CYLINDER,

    PHY_MAX_ITEM_TYPES
};

#if !defined FLOAT_INFINITY
	#define FLOAT_INFINITY   (Float:0x7F800000)
#endif
#if !defined FLOAT_NEG_INFINITY
	#define FLOAT_NEG_INFINITY (Float:0xFF800000)
#endif
#if !defined FLOAT_NAN
	#define FLOAT_NAN	 (Float:0xFFFFFFFF)
#endif

// Natives / Functions

native PHY_InitObject(objectid, modelid = 0, Float:mass = 1.0, Float:size = FLOAT_NAN, mode = PHY_MODE_3D);
native PHY_DeleteObject(objectid);
native PHY_SetObjectVelocity(objectid, Float:vx, Float:vy, Float:vz = 0.0);
native PHY_GetObjectVelocity(objectid, &Float:vx, &Float:vy, &Float:vz);
native PHY_GetHandleObject(handleid);
native PHY_SetObjectFriction(objectid, Float:friction);
native PHY_RollObject(objectid, bool:toggle = true, rollingmode = PHY_ROLLING_MODE_DEFAULT);
native PHY_SetObjectWorld(objectid, world);
native PHY_SetObjectAirResistance(objectid, Float:resistance);
native PHY_GetObjectMoveAngle(objectid, &Float:moveangle);
native PHY_GetObjectSpeed(objectid, &Float:speed, _3D = 0);
native PHY_SetObjectZBound(objectid, Float:low = FLOAT_NAN, Float:high = FLOAT_NAN, Float:constant = 0.0);
native PHY_SetObjectGravity(objectid, Float:gravity);
native PHY_SetObjectAcceleration(objectid, Float:ax, Float:ay, Float:az = 0.0);
native PHY_GetObjectAcceleration(objectid, &Float:ax, &Float:ay, &Float:az);
native PHY_ToggleObjectPlayerColls(objectid, toggle = 1, Float:constant = 1.0, Float:distoffset = 0.8, Float:zoffsetlow = 1.0, Float:zoffsethigh = 1.0);

native PHY_CreateWall(Float:x1, Float:y1, Float:x2, Float:y2, Float:constant = 1.0, Float:low = FLOAT_NEG_INFINITY, Float:high = FLOAT_INFINITY);
native PHY_DestroyWall(wallid);
native PHY_SetWallWorld(wallid, world);

native PHY_CreateCylinder(Float:x, Float:y, Float:size, Float:constant = 1.0, Float:low = FLOAT_NEG_INFINITY, Float:high = FLOAT_INFINITY);
native PHY_DestroyCylinder(cylinderid);
native PHY_SetCylinderWorld(cylinderid, world);

native PHY_SetUpdateInterval(interval_ms);
native PHY_CountItems(type);
native PHY_SetPlayerWorld(playerid, world);

stock PHY_CreateArea(Float:minX, Float:minY, Float:maxX, Float:maxY, Float:constant = 1.0, Float:low = FLOAT_NEG_INFINITY, Float:high = FLOAT_INFINITY)
{
	PHY_CreateWall(minX, minY, minX, maxY, constant, low, high);
	PHY_CreateWall(minX, maxY, maxX, maxY, constant, low, high);
	PHY_CreateWall(maxX, maxY, maxX, minY, constant, low, high);
	PHY_CreateWall(maxX, minY, minX, minY, constant, low, high);
}

stock PHY_CreateAreaEx(dest_walls[4], Float:minX, Float:minY, Float:maxX, Float:maxY, Float:constant = 1.0, Float:low = FLOAT_NEG_INFINITY, Float:high = FLOAT_INFINITY, world = 0)
{
	dest_walls[0] = PHY_CreateWall(minX, minY, minX, maxY, constant, low, high);
	dest_walls[1] = PHY_CreateWall(minX, maxY, maxX, maxY, constant, low, high);
	dest_walls[2] = PHY_CreateWall(maxX, maxY, maxX, minY, constant, low, high);
	dest_walls[3] = PHY_CreateWall(maxX, minY, minX, minY, constant, low, high);

	for(new i = 0; i < sizeof(dest_walls); i++)
	{
		PHY_SetWallWorld(dest_walls[i], world);
	}
}

// Callbacks

forward PHY_OnObjectUpdate(handleid);
forward PHY_OnObjectCollideWithObject(handleid_a, handleid_b);
forward PHY_OnObjectCollideWithZBound(handleid, lowhigh); // low bound = 0, high bound = 1
forward PHY_OnObjectCollideWithSAWorld(objectid, Float:cx, Float:cy, Float:cz);
forward PHY_OnObjectCollideWithWall(handleid, wallid);
forward PHY_OnObjectCollideWithCylinder(handleid, cylinderid);
forward PHY_OnObjectCollideWithPlayer(handleid, playerid);