#include "pointers.hpp"
#include "Callbacks.hpp"
#include <sampgdk.h>
#include <unordered_set>

int Callbacks::OnObjectUpdate(int objectid)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectUpdate", &amxIndex))
		{
			amx_Push(a, (cell)objectid);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}

int Callbacks::OnObjectCollideWithObject(int object1, int object2)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectCollideWithObject", &amxIndex))
		{
			amx_Push(a, (cell)object2);
			amx_Push(a, (cell)object1);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}

int Callbacks::OnObjectCollideWithWall(int objectid, int wallid)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectCollideWithWall", &amxIndex))
		{
			amx_Push(a, (cell)wallid);
			amx_Push(a, (cell)objectid);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}

int Callbacks::OnObjectCollideWithPlayer(int objectid, int playerid)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectCollideWithPlayer", &amxIndex))
		{
			amx_Push(a, (cell)playerid);
			amx_Push(a, (cell)objectid);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}

int Callbacks::OnObjectCollideWithCylinder(int objectid, int cylinderid)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectCollideWithCylinder", &amxIndex))
		{
			amx_Push(a, (cell)cylinderid);
			amx_Push(a, (cell)objectid);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}

int Callbacks::OnObjectCollideWithZBound(int objectid, int lowhigh)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectCollideWithZBound", &amxIndex))
		{
			amx_Push(a, (cell)lowhigh);
			amx_Push(a, (cell)objectid);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}