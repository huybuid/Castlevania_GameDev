#include "Ghost.h"
#include <cstdlib>
#include <time.h>
#include "PlayScence.h"


void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD tick = GetTickCount();
	if (tick - switch_time > GHOST_SWITCH_TIME && switch_time > 0)
	{
		float simon_x, simon_y;
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(simon_x, simon_y);
		if (x < simon_x) nx = 1;
		else nx = -1;
		if (y < simon_y) ny = 1;
		else ny = -1;
		srand(time(NULL));
		int random = rand() % 2;
		if (random == 0)
		{
			//Ghost fly high
			vx = nx * GHOST_SPEED_SLOW;
			vy = ny * GHOST_SPEED_FAST;
		}
		else
		{
			//Ghost fly low
			vx = nx * GHOST_SPEED_FAST;
			vy = ny * GHOST_SPEED_SLOW;
		}
		switch_time = tick;
	}
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void Ghost::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y, nx);
	//RenderBoundingBox();
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y + GHOST_BBOX_HEIGHT;
}

Ghost::~Ghost()
{
}
