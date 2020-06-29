#include <iostream>
#include <fstream>

#include "Simon.h"
#include "BackGround.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "FirePillar.h"
#include "Whip.h"
#include "Grid.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN			-1

#define SCENE_SECTION_OBJECTS			6
#define SCENE_SECTION_BACKGROUND		7

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_FIREPILLAR	2
#define OBJECT_TYPE_WHIP	3
#define OBJECT_TYPE_CANDLE	4
#define OBJECT_TYPE_STAIRS	5
#define OBJECT_TYPE_ZOMBIE	6
#define OBJECT_TYPE_KNIGHT	7
#define OBJECT_TYPE_BAT		8

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);


	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 8) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	int grid_x = atoi(tokens[1].c_str());
	int	grid_y = atoi(tokens[2].c_str());
	float x = atof(tokens[4].c_str());
	float y = atof(tokens[5].c_str());
	float w = atof(tokens[6].c_str());
	float h = atof(tokens[7].c_str());
	int nx = atoi(tokens[8].c_str());
	int type = atoi(tokens[9].c_str());
	int item_id = atoi(tokens[10].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	CItem *item = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] SIMON object was created before, starting soft-reset!\n");
			player->Reset(x,y, nx);
			return;
		}
		obj = new CSimon(x, y, nx);
		player = (CSimon*)obj;
		player->whip = new Whip();
		player->whip->SetAnimationSet(animation_sets->Get(3));
		DebugOut(L"[INFO] Player object created!\n");
		break;
	default:
		CGrid::GetInstance()->Insert(object_type, grid_x, grid_y, x, y, w, h, nx, type, item_id);
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
}

void CPlayScene::_ParseSection_BACKGROUND(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return; //if invalid line => skip; a background must have a path and background ID
	background.SetPath(tokens[0]);
	background.Load(atoi(tokens[1].c_str()));
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[BACKGROUND]") {
			section = SCENE_SECTION_BACKGROUND; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_BACKGROUND: _ParseSection_BACKGROUND(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	CGrid* grid = CGrid::GetInstance();
	vector<LPGAMEOBJECT> coObjects;
	float x, y;
	CGame *game = CGame::GetInstance();
	game->GetCamPos(x, y);
	grid->GetListObject(coObjects, x, y);
	player->Update(dt,&coObjects);
	player->whip->Update(dt, &coObjects);
	for (size_t i = 0; i < weapons.size(); i++)
	{
		weapons[i]->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt, &coObjects);
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	cx -= game->GetScreenWidth() / 2 - 16;
	if (cx < 0) { cx = 0; }
	if (cx > background.screen_limit - SCREEN_WIDTH) { cx = background.screen_limit - SCREEN_WIDTH; }
	cy -= game->GetScreenHeight() / 2;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

void CPlayScene::Render()
{
	float x, y;
	CGame::GetInstance()->GetCamPos(x, y);
	background.Render(x,y);
	CGrid::GetInstance()->GetListObject(objects, x, y);
	player->Render();
	player->whip->Render();
	for (size_t i = 0; i < weapons.size(); i++)
	{
		weapons[i]->Render();
	}
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isActive)
			objects[i]->Render();
	}
	for (size_t i = 0; i < items.size(); i++)
	{
		items[i]->Render();
	}
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	if (CGrid::GetInstance())
		CGrid::GetInstance()->Clear();
	items.clear();
	weapons.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();
	/* CMario *mario = ((CPlayScene*)scence)->GetPlayer()
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A: 
		mario->Reset();
		break;
	} */
	switch (KeyCode)
	{
	case DIK_X:
		if (!simon->isAttack && !simon->isDuck && !simon->isJump)
		{
			simon->SetState(SIMON_STATE_JUMP);
		}
		break;
	case DIK_A:
		simon->Reset(simon->start_x, simon->start_y);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Simon die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (!game->IsKeyDown(DIK_DOWN))
	{
		if (simon->GetState() == SIMON_STATE_DUCKING)
		{
			simon->SetState(SIMON_STATE_IDLE);
			simon->y -= 8;
		}
		if (simon->GetState()==SIMON_STATE_DUCKATK) 
		{
			if (GetTickCount() - simon->attack_start > SIMON_ATTACK_TIME  && simon->attack_start > 0) //wait for Simon to finish attack animation
			{
				simon->isDuck = 0;
				simon->y -= 8;
			}
		}
	}
	else
	{
		if (simon->isAttack)
		{
			if (simon->attack_start <= 0)
			{
				simon->SetState(SIMON_STATE_DUCKING);
			}
		}
		else
		{
			if (!simon->isJump && !simon->isDuck)
			{
				simon->SetState(SIMON_STATE_DUCKING);
			}
		}
	}
	if (!simon->isAttack) //disable keys when attacking
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (!simon->isJump)
			{
				simon->nx = 1;
				if (!simon->isDuck)
					simon->vx = SIMON_WALKING_SPEED * simon->nx;
			}
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (!simon->isJump)
			{
				simon->nx = -1;
				if (!simon->isDuck)
					simon->vx = SIMON_WALKING_SPEED * simon->nx;
			}
		}
		else
		{
			if (!simon->isDuck && !simon->isAttack)
				simon->SetState(SIMON_STATE_IDLE);
		}
	}
	if (game->IsKeyDown(DIK_Z))
	{
		if (!simon->isAttack)
		{
			simon->StartAttackSequence(!game->IsKeyDown(DIK_UP)); //if the UP key is pressed, try to fire extra weapon
		}
	}
}

