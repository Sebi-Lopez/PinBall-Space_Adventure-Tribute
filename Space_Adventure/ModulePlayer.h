#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class PhysBody;
class b2RevoluteJoint;
class b2DistanceJoint; 


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	uint lifes;
	b2DistanceJoint* kicker = nullptr; 
	b2RevoluteJoint* flipper_left = nullptr;
	b2RevoluteJoint* flipper_right = nullptr;
};