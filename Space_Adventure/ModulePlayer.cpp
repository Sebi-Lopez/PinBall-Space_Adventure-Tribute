#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	b2RevoluteJointDef jointDef;

	int flipper_points_l[20] = {
	1, 16,
	5, 22,
	65, 45,
	71, 43,
	73, 38,
	70, 32,
	15, 3,
	9, 3,
	2, 9,
	1, 16
	};



	PhysBody* flipper_body = App->physics->CreatePolygon(120, 671, flipper_points_l, 20);



	PhysBody* anchor_l = App->physics->CreateCircle(130, 681, PIXEL_TO_METERS(500), b2_staticBody);


	b2RevoluteJointDef defJoint; 
	defJoint.bodyA = flipper_body->body; 
	defJoint.bodyB = anchor_l->body;	
	defJoint.collideConnected = false;
	defJoint.localAnchorA = anchor_l->body->GetLocalCenter();
	defJoint.localAnchorB = { PIXEL_TO_METERS(0) ,  PIXEL_TO_METERS(0) };
	defJoint.lowerAngle = 0 * DEGTORAD;
	defJoint.upperAngle = 60 * DEGTORAD;
	defJoint.enableLimit = true; 

	b2RevoluteJoint* left_joint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&defJoint);
	
		
			

	/*int flipper_points_r[20] = {
	3, 39,
	4, 33,
	62, 3,
	67, 3,
	74, 11,
	74, 17,
	70, 23,
	13, 45,
	6, 44,
	2, 39
	};

	PhysBody* flipper_body_r = App->physics->CreatePolygon(120, 671, flipper_points_r, 20);
	PhysBody* anchor_r = App->physics->CreateCircle(285, 683, PIXEL_TO_METERS(500), b2_staticBody);*/
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}



