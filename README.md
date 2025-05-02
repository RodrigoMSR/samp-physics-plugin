# SA-MP Physics Plugin

This is the plugin version of the [SA-MP Physics include by Peppe](https://github.com/uPeppe/physics.inc). This plugin uses dynamic objects and requires the Streamer plugin.

Advantages of the plugin compared to include:
- Performance (tested with 320 objects and 100 walls, no impact on the server tick rate).
- Use of dynamic objects (allows, for example, multiple pool tables in separate virtual worlds).
- Better accuracy in the timing of updates, which is important for smoother movement. While a 20ms SA-MP timer is called about 32 times per second, in the plugin it is 47-49 times per second (not ideal due to the dependence on ProcessTick).

## Example usage
```pawn
#include <a_samp>
#include <zcmd>
#include <streamer>
#include <physics_plugin>

CMD:throwball(playerid)
{
	const ballModel = 2114;
	const Float:distance = 1.0;
	const Float:speed = 5.0;

	new Float:x, Float:y, Float:z, Float:a;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));

	new objectid = CreateDynamicObject(ballModel, x, y, z+0.5, 0.0, 0.0, 0.0);
	
	PHY_InitObject(objectid, ballModel);
	PHY_SetObjectGravity(objectid, 10.0);
	PHY_SetObjectZBound(objectid, z-0.85);
	PHY_RollObject(objectid, true);
	PHY_SetObjectFriction(objectid, 3.0);

	PHY_SetObjectVelocity(
		objectid,
		(speed * floatsin(-a, degrees)),
		(speed * floatcos(-a, degrees)),
		2.0
	);

	Streamer_Update(playerid);
	return 1;
}

public PHY_OnObjectCollideWithZBound(objectid, lowhigh)
{
	PhyObjectPlaySound(objectid, 4600);
	return 1;
}

public PHY_OnObjectCollideWithObject(object1, object2)
{
	PhyObjectPlaySound(object1, 4600);
	return 1;
}

PhyObjectPlaySound(objectid, soundid)
{
	new Float:x, Float:y, Float:z;
	GetDynamicObjectPos(objectid, x, y, z);

	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerInRangeOfPoint(i, 30.0, x, y, z))
		{
			PlayerPlaySound(i, soundid, x, y, z);
		}
	}
	return 1;
}
```
