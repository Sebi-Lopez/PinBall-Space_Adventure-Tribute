#ifndef MODULEMAINSTAGE__H
#define MODULEMAINSTAGE__H

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
struct SDL_Texture; 

class ModuleMainStage : public Module
{
public:
	ModuleMainStage(Application* app, bool start_enabled = true);
	~ModuleMainStage();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
};

#endif // MODULEMAINSTAGE__H