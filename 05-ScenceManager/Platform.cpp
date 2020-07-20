#include "Platform.h"

void Platform::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	DWORD tick = GetTickCount();
	if (tick - stop_start > STOP_TIME && stop_start > 0)
	{
		stop_start = 0;
		vx = nx * PLATFORM_SPEED_X;
	}
	x += dx;
	if (x < limit_l)
	{
		x = limit_l;
		ChangeDirection();
	}
	else if (x > limit_r)
	{
		x = limit_r;
		ChangeDirection();
	}
}

void Platform::Render()
{
	animation_set->at(0)->Render(x, y, 1);
	//RenderBoundingBox();
}

void Platform::ChangeDirection()
{
	nx = -nx;
	vx = 0;
	stop_start = GetTickCount();
}

void Platform::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + PLATFORM_BBOX_WIDTH;
	bottom = y + PLATFORM_BBOX_HEIGHT;
}

Platform::~Platform()
{
}
