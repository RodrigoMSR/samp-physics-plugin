#pragma once

namespace Callbacks
{
	int OnObjectUpdate(int objectid);
	int OnObjectCollideWithObject(int object1, int object2);
	int OnObjectCollideWithWall(int objectid, int wallid);
	int OnObjectCollideWithPlayer(int objectid, int playerid);
	int OnObjectCollideWithCylinder(int objectid, int cylinderid);
	int OnObjectCollideWithZBound(int objectid, int lowhigh);
	int OnObjectCollideWithSAWorld(int objectid, float cx, float cy, float cz);
}