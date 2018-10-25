#ifndef MODULEMAINSTAGE__H
#define MODULEMAINSTAGE__H

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
struct SDL_Texture; 

struct SensorType {
	PhysBody* Death = nullptr;
	PhysBody* Box1 = nullptr;
	PhysBody* Box2 = nullptr;
	PhysBody* Box3 = nullptr;
	bool Box1A = false;
	bool Box2A = false;
	bool Box3A = false;
};

class ModuleMainStage : public Module
{
public:
	ModuleMainStage(Application* app, bool start_enabled = true);
	~ModuleMainStage();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);


	void CreateStage(); 
	void Sensors();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> chains; 
	PhysBody* Ball;
	PhysBody* sensor;
	bool sensed;
	SensorType Sens;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* background_texture; 

	uint bonus_fx;
};

#endif // MODULEMAINSTAGE__H