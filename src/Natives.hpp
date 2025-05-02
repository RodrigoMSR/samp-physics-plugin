#pragma once

#include <sampgdk.h>

#define CHECK_PARAMS(n) \
	if (params[0] != (n * 4)) \
	{ \
		sampgdk::logprintf("%s: Expecting %d parameter(s), but found %d.", __func__, n, params[0] / sizeof(cell)); \
		return 0; \
	}

namespace Natives
{
	cell AMX_NATIVE_CALL PHY_InitObject(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PHY_CreateWall(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetObjectVelocity(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_GetObjectVelocity(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_DeleteObject(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_DestroyWall(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetObjectFriction(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_RollObject(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetWallWorld(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetObjectWorld(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetObjectAirResistance(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_GetObjectMoveAngle(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetUpdateInterval(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_CountItems(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetObjectZBound(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetObjectGravity(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetObjectAcceleration(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_GetObjectAcceleration(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_ToggleObjectPlayerColls(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_CreateCylinder(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_DestroyCylinder(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetCylinderWorld(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_GetObjectSpeed(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_SetPlayerWorld(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_GetColSphereRadius(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_GetColSphereOffset(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_GetColCount(AMX* amx, cell* params);
    cell AMX_NATIVE_CALL PHY_UseColAndreas(AMX* amx, cell* params);
}