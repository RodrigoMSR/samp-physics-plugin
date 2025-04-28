# SA-MP Physics Plugin

This plugin is a "port" of the [SA-MP Physics include by Peppe](https://github.com/uPeppe/physics.inc). This plugin uses dynamic objects and requires the Streamer plugin.

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

	new dynamicObject = CreateDynamicObject(ballModel, x, y, z+0.5, 0.0, 0.0, 0.0);
	new objectid = PHY_InitObject(dynamicObject, ballModel);

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
```