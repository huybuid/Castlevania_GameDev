#include "Ghost.h"
#include <cstdlib>
#include <time.h>
#include "PlayScence.h"


void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float simon_x, simon_y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(simon_x, simon_y);
	if (nx > 0)
	{
		if (simon_x > trigger_x && trigger_x != -1)
			isActive = true;
	}
	else
	{
		if (simon_x < trigger_x && trigger_x != -1)
			isActive = true;
	}
	if (!isActive) return;
	DWORD tick = GetTickCount();
	if (freeze_start > 0)
	{
		if (isDamaged)
		{
			if (tick - damage_start > DAMAGE_FREEZE_TIME)
			{
				isDamaged = false;
				damage_start = 0;
			}
		}
		if (tick - freeze_start > freeze_time)
		{
			freeze_start = 0;
			freeze_time = 0;
		}
		return;
	}
	if (tick - switch_time > GHOST_SWITCH_TIME && switch_time > 0)
	{
		if (x < simon_x) nx = 1;
		else nx = -1;
		if (y < simon_y) ny = 1;
		else ny = -1;
		srand(time(NULL));
		int random = rand() % 3;
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
	if (freeze_start == 0)
		animation_set->at(state)->Render(x, y, nx);
	else animation_set->at(state)->FreezeRender(x, y, nx);
	//RenderBoundingBox();
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y + GHOST_BBOX_HEIGHT;
}

void Ghost::Destroy()
{
	CEnemy::Destroy();
	trigger_x = -1;
}

Ghost::~Ghost()
{
}
