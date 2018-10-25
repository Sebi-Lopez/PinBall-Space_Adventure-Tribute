#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"

class PhysBody;


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
	PhysBody* kicker = nullptr; 
	b2Vec2 impulse = { 0, 0 };
	b2RevoluteJoint* flipper_left = nullptr;
	b2RevoluteJoint* flipper_right = nullptr;
};