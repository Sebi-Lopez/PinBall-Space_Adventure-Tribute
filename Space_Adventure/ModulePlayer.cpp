#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	ball = CBall();
	b2RevoluteJointDef jointDef;
	lifes = 3;

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
	b2Vec2 anchor_A_l = anchor_l->body->GetLocalCenter(); 
	b2Vec2 anchor_B_l = { PIXEL_TO_METERS (10) , PIXEL_TO_METERS(11) };
	App->physics->CreateRevolutionJoint(anchor_l, flipper_body, anchor_A_l, anchor_B_l, 0, -50);
	
	

	int flipper_points_r[20] = {
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
	PhysBody* anchor_r = App->physics->CreateCircle(285, 683, PIXEL_TO_METERS(500), b2_staticBody);
	b2Vec2 anchor_A_r = anchor_r->body->GetLocalCenter();
	b2Vec2 anchor_B_r = { PIXEL_TO_METERS(62), PIXEL_TO_METERS(14)};
	App->physics->CreateRevolutionJoint(anchor_r, flipper_body_r, anchor_A_r, anchor_B_r, 0, 60);


	kicker = App->physics->CreateRectangle(433, 650, 25, 10, b2_dynamicBody);
	PhysBody* kicker_anchor = App->physics->CreateRectangle(433, 700, 5, 10, b2_staticBody);

	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = kicker->body;
	prismaticJointDef.bodyB = kicker_anchor->body;
	prismaticJointDef.localAnchorA = kicker->body->GetLocalCenter();
	prismaticJointDef.localAnchorB = kicker_anchor->body->GetLocalCenter();
	prismaticJointDef.localAxisA = { 0.0f,1.0f };
	prismaticJointDef.collideConnected = true;

	b2PrismaticJoint* kicker_joint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&prismaticJointDef);

	b2DistanceJointDef distanceJointDef;
	distanceJointDef.bodyA = kicker->body;
	distanceJointDef.bodyB = kicker_anchor->body;
	distanceJointDef.localAnchorA = kicker->body->GetLocalCenter();
	distanceJointDef.localAnchorB = kicker_anchor->body->GetLocalCenter();

	distanceJointDef.collideConnected = true;

	distanceJointDef.frequencyHz = 7.f;
	distanceJointDef.dampingRatio = 0.3f;

	b2DistanceJoint* kicker_djoint = (b2DistanceJoint*)App->physics->world->CreateJoint(&distanceJointDef);


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
	if (App->input->GetKey(5) == KEY_REPEAT) {

		if (impulse.y < 100.0f)
			impulse.y += 2.0f;

		kicker->body->ApplyForce(impulse, { 0.0f, 0.0f }, true);
	}

	if (App->input->GetKey(5) == KEY_UP) {

		kicker->body->ApplyForce({ 0.0f, -impulse.y * 5.0f }, { 0.0f, 0.0f }, true);
		impulse = { 0.0f,0.0f };
	}
	

	if (resetBall)
		ResetBall();
	return UPDATE_CONTINUE;
}



PhysBody * ModulePlayer::CBall()
{
	InitialPos.x = 203;
	InitialPos.y = 570;
	PhysBody* ballPB = App->physics->CreateCircle(InitialPos.x, InitialPos.y, 5, b2_dynamicBody);
	ballPB->listener = (Module*)App->main_stage;
	return ballPB;
}

PhysBody* ModulePlayer::GetBall()
{
	return ball;
}

void ModulePlayer::ResetBall()
{
	if (ball->body != nullptr) {
		App->physics->world->DestroyBody(ball->body);
		ball = nullptr;
	}

	lifes--;
	
	if (lifes > 0)
		ball = CBall();

	resetBall = false;
}