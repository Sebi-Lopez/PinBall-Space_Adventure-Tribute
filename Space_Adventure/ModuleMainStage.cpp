#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMainStage.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"

ModuleMainStage::ModuleMainStage(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	sensed = false;
}

ModuleMainStage::~ModuleMainStage()
{}

// Load assets
bool ModuleMainStage::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->physics->Enable();
	App->player->Enable();

	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	circle = App->textures->Load("pinball/wheel.png");
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	background_texture = App->textures->Load("pinball/background.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	initballx = 198;
	initbally = 600;
	Ball = BallC();


	CreateStage();
	Sensors();

	return ret;
	if (Sens.Box1A && Sens.Box2A && Sens.Box3A) {
		// Subes la score + 300;
		Sens.Box1A = false;
		Sens.Box2A = false;
		Sens.Box3A = false;

	}
}

// Load assets
bool ModuleMainStage::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleMainStage::Update()
{

	App->renderer->Blit(background_texture, 0, 0);
	
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64, b2_staticBody));
	}

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleMainStage::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	

	if (bodyB == Sens.Death && bodyA == Ball) {
		if (Ball->body != nullptr) {
			App->physics->world->DestroyBody(Ball->body);
		}

		App->player->lifes--;
		//Play death sound
		//App->audio->PlayFx(App->audio->GetFX().deathSound);

		
		if (App->player->lifes > 0) {
			BallC();
		}
	
		

	

	}
	else {

		if (bodyB == Sens.Box1 && bodyA == Ball) {
			// subir score + 30;
			Sens.Box1A = true;
		}
		if (bodyB == Sens.Box2 && bodyA == Ball) {
			// subir score + 30;
			Sens.Box2A = true;
		}
		if (bodyB == Sens.Box3 && bodyA == Ball) {
			// subir score + 30;
			Sens.Box3A = true;

		}
	}

	
}

void ModuleMainStage::CreateStage()
{
	int back_ground[146] = {
	39, 115,
	54, 97,
	77, 73,
	104, 51,
	142, 28,
	181, 16,
	213, 11,
	264, 11,
	302, 18,
	332, 28,
	358, 43,
	388, 70,
	412, 100,
	426, 122,
	438, 154,
	445, 187,
	445, 239,
	445, 458,
	445, 531,
	445, 619,
	445, 708,
	441, 717,
	427, 717,
	422, 709,
	422, 597,
	422, 212,
	416, 176,
	407, 148,
	389, 115,
	356, 80,
	346, 80,
	339, 84,
	339, 117,
	344, 122,
	370, 122,
	389, 206,
	337, 320,
	338, 326,
	346, 330,
	353, 330,
	381, 267,
	395, 236,
	406, 269,
	375, 348,
	368, 374,
	367, 490,
	381, 507,
	414, 541,
	414, 664,
	413, 673,
	406, 680,
	385, 691,
	351, 706,
	296, 733,
	275, 741,
	275, 767,
	458, 768,
	458, 2,
	0, 1,
	0, 768,
	135, 768,
	134, 742,
	14, 686,
	9, 678,
	8, 550,
	38, 519,
	38, 506,
	11, 478,
	11, 207,
	13, 182,
	22, 150,
	30, 130,
	39, 115
	};

	chains.add(App->physics->CreateChain(0, 0, back_ground, 146, b2_staticBody));

	int Bumper_Left[16] = {
	1, 95,
	2, 100,
	12, 111,
	55, 94,
	54, 2,
	50, 1,
	38, 15,
	1, 95
	};

	chains.add(App->physics->CreateChain(305, 532, Bumper_Left, 16, b2_staticBody));


	int donut[34] = {
	1, 41,
	1, 29,
	6, 17,
	15, 7,
	28, 1,
	43, 1,
	55, 6,
	64, 16,
	69, 29,
	69, 42,
	65, 55,
	58, 65,
	45, 71,
	28, 71,
	15, 66,
	5, 55,
	1, 41
	};

	chains.add(App->physics->CreateChain(258, 232, donut, 34, b2_staticBody));
	chains.add(App->physics->CreateChain(194, 176, donut, 34, b2_staticBody));
	chains.add(App->physics->CreateChain(283, 158, donut, 34, b2_staticBody));

	int Bumper_Right[14] = {
		8, 1,
		20, 15,
		57, 98,
		46, 110,
		4, 94,
		4, 3,
		8, 1
	};
	chains.add(App->physics->CreateChain(65, 531, Bumper_Right, 14, b2_staticBody));

	int Coll_Orange[18] = {
		7, 2,
		14, 2,
		19, 8,
		19, 38,
		14, 43,
		7, 43,
		2, 39,
		1, 8,
		7, 2
	};
	chains.add(App->physics->CreateChain(294, 92, Coll_Orange, 18, b2_staticBody));

	int Coll_Blue[18] = {
		3, 9,
		9, 2,
		16, 2,
		22, 9,
		22, 40,
		16, 45,
		9, 45,
		3, 39,
		3, 9
	};
	chains.add(App->physics->CreateChain(202, 101, Coll_Blue, 18, b2_staticBody));

	int Coll_Green[18] = {
		2, 7,
		8, 2,
		16, 2,
		21, 8,
		21, 36,
		16, 42,
		8, 42,
		2, 36,
		2, 7
	};

	chains.add(App->physics->CreateChain(251, 102, Coll_Green, 18, b2_staticBody));

	int Jackpot[40] = {
		3, 127,
		1, 109,
		8, 86,
		25, 55,
		45, 32,
		62, 15,
		69, 10,
		75, 2,
		97, 5,
		97, 36,
		77, 64,
		53, 96,
		38, 118,
		23, 146,
		21, 152,
		21, 160,
		18, 163,
		14, 159,
		7, 143,
		3, 127
	};
	chains.add(App->physics->CreateChain(38, 78, Jackpot, 40, b2_staticBody));

	int Monster_eye[72] = {
		53, 96,
		77, 66,
		91, 44,
		94, 30,
		95, 8,
		99, 3,
		108, 3,
		113, 8,
		113, 33,
		110, 41,
		111, 132,
		113, 141,
		141, 169,
		161, 198,
		168, 213,
		167, 233,
		159, 215,
		140, 190,
		112, 164,
		97, 146,
		85, 133,
		77, 130,
		64, 132,
		50, 145,
		35, 170,
		23, 196,
		18, 212,
		17, 235,
		10, 226,
		5, 218,
		3, 201,
		6, 182,
		20, 155,
		28, 140,
		47, 106,
		53, 96
	};
	chains.add(App->physics->CreateChain(66, 91, Monster_eye, 72, b2_staticBody));

	int Coll_Metal[28] = {
		4, 60,
		74, 59,
		78, 55,
		78, 49,
		68, 35,
		52, 18,
		36, 3,
		30, 1,
		20, 5,
		9, 23,
		1, 42,
		0, 51,
		1, 56,
		4, 60
	};
	chains.add(App->physics->CreateChain(114, 265, Coll_Metal, 28, b2_staticBody));

	int Coll_Metal_Right[26] = {
		2, 121,
		101, 83,
		100, 11,
		97, 7,
		100, 1,
		106, 1,
		110, 6,
		108, 11,
		108, 90,
		7, 139,
		9, 131,
		7, 126,
		2, 121
	};
	chains.add(App->physics->CreateChain(286, 550, Coll_Metal_Right, 26, b2_staticBody));

	int Coll_Metal_Left[30] = {
		3, 58,
		3, 91,
		104, 139,
		103, 133,
		104, 126,
		110, 122,
		11, 83,
		11, 12,
		14, 7,
		12, 3,
		8, 1,
		3, 3,
		1, 7,
		3, 11,
		3, 58
	};
	chains.add(App->physics->CreateChain(28, 552, Coll_Metal_Left, 30, b2_staticBody));
	

}

void ModuleMainStage::Sensors() {

	Sens.Box1 = App->physics->CreateRectangleSensor(117+10,322+10,21,20,this);
	Sens.Box2 = App->physics->CreateRectangleSensor(141+10,322+10, 21, 20,this);
	Sens.Box3 = App->physics->CreateRectangleSensor(165+10,322+10, 21, 20,this);
	Sens.Death = App->physics->CreateRectangleSensor(0, 820, 600, 40, this);


}

PhysBody * ModuleMainStage::BallC() {
	
	PhysBody* ballPB = App->physics->CreateCircle(initballx, initbally, 5, b2_dynamicBody);
	ballPB->listener = this;
	return ballPB;
}