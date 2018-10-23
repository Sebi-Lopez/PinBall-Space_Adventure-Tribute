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

	CreateStage();

	return ret;
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
	int x, y;

	App->audio->PlayFx(bonus_fx);


	if (bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if (bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
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

	chains.add(App->physics->CreateChain(308, 532, Bumper_Left, 16, b2_staticBody));


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

}
