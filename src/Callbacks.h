#pragma once

namespace Callbacks
{
	int OnObjectUpdate(int handleid);
	int OnObjectCollideWithObject(int handleid_a, int handleid_b);
	int OnObjectCollideWithWall(int handleid, int wallid);
}