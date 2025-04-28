#include <unordered_set>
#include <sampgdk.h>
#include "Manager.hpp"
#include "Natives.hpp"

#define PLUGIN_NAME "Physics"
#define PLUGIN_VERSION "1.0"

extern void *pAMXFunctions;

std::unordered_set<AMX*>* g_Interfaces = NULL;
Manager* g_Manager = NULL;

//--- Callbacks

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	//static unsigned int tickTime = 0, tickCount = 0;

	if(!g_Manager) return;
	
	if(g_Manager->shouldUpdate())
	{
		g_Manager->update();

		//tickCount++;
	}

	/*
	if(GetTickCount() - tickTime >= 1000)
	{
		sampgdk::logprintf(" %d ticks", tickCount);

		tickTime = GetTickCount();
		tickCount = 0;
	}*/
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if(playerid >= 0 && playerid < MAX_PLAYERS)
	{
		if(g_Manager != NULL)
			g_Manager->addPlayer(playerid);
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	if(g_Manager != NULL)
		g_Manager->deletePlayer(playerid);
	
	return true;
}

//--- Plugin Load / Unload

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];

	g_Interfaces = new std::unordered_set<AMX*>();
	g_Manager = new Manager();

	sampgdk::logprintf("  %s v%s Loaded.", PLUGIN_NAME, PLUGIN_VERSION);
	
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	delete g_Manager;
	delete g_Interfaces;

	sampgdk::logprintf("  %s v%s Unloaded.", PLUGIN_NAME, PLUGIN_VERSION);
	sampgdk::Unload();
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

//--- Natives List

AMX_NATIVE_INFO PluginNatives[] =
{
	{"PHY_InitObject", Natives::PHY_InitObject},
	{"PHY_CreateWall", Natives::PHY_CreateWall},
	{"PHY_SetObjectVelocity", Natives::PHY_SetObjectVelocity},
	{"PHY_GetObjectVelocity", Natives::PHY_GetObjectVelocity},
	{"PHY_DeleteObject", Natives::PHY_DeleteObject},
	{"PHY_DestroyWall", Natives::PHY_DestroyWall},
	{"PHY_GetDynamicObject", Natives::PHY_GetDynamicObject},
	{"PHY_SetObjectFriction", Natives::PHY_SetObjectFriction},
	{"PHY_RollObject", Natives::PHY_RollObject},
	{"PHY_SetWallWorld", Natives::PHY_SetWallWorld},
	{"PHY_SetObjectWorld", Natives::PHY_SetObjectWorld},
	{"PHY_SetObjectAirResistance", Natives::PHY_SetObjectAirResistance},
	{"PHY_GetObjectMoveAngle", Natives::PHY_GetObjectMoveAngle},
	{"PHY_SetUpdateInterval", Natives::PHY_SetUpdateInterval},
	{"PHY_CountItems", Natives::PHY_CountItems},
	{"PHY_SetObjectZBound", Natives::PHY_SetObjectZBound},
	{"PHY_SetObjectGravity", Natives::PHY_SetObjectGravity},
	{"PHY_SetObjectAcceleration", Natives::PHY_SetObjectAcceleration},
	{"PHY_GetObjectAcceleration", Natives::PHY_GetObjectAcceleration},
	{"PHY_ToggleObjectPlayerColls", Natives::PHY_ToggleObjectPlayerColls},
	{"PHY_CreateCylinder", Natives::PHY_CreateCylinder},
	{"PHY_DestroyCylinder", Natives::PHY_DestroyCylinder},
	{"PHY_SetCylinderWorld", Natives::PHY_SetCylinderWorld},
	{"PHY_GetObjectSpeed", Natives::PHY_GetObjectSpeed},
	{"PHY_SetPlayerWorld", Natives::PHY_SetPlayerWorld},
	{"PHY_GetColSphereRadius", Natives::PHY_GetColSphereRadius},
	{"PHY_GetColSphereOffset", Natives::PHY_GetColSphereOffset},
	{"PHY_GetColCount", Natives::PHY_GetColCount},
	
	{0, 0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) 
{
	g_Interfaces->insert(amx);

	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) 
{
	g_Interfaces->erase(amx);

	return AMX_ERR_NONE;
}