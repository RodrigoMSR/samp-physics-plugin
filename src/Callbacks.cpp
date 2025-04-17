#include "pointers.h"
#include "Callbacks.h"
#include <sampgdk.h>
#include <unordered_set>

int Callbacks::OnObjectUpdate(int handleid)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectUpdate", &amxIndex))
		{
			amx_Push(a, (cell)handleid);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}

int Callbacks::OnObjectCollideWithObject(int handleid_a, int handleid_b)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectCollideWithObject", &amxIndex))
		{
			amx_Push(a, (cell)handleid_b);
			amx_Push(a, (cell)handleid_a);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}

int Callbacks::OnObjectCollideWithWall(int handleid, int wallid)
{
	int amxIndex = 0;

	for(AMX* a : *g_Interfaces)
	{
		if(!amx_FindPublic(a, "PHY_OnObjectCollideWithWall", &amxIndex))
		{
			amx_Push(a, (cell)wallid);
			amx_Push(a, (cell)handleid);
			amx_Exec(a, NULL, amxIndex);
		}
	}
	return 1;
}