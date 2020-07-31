#include "SmallHeart.h"

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActive) return;
	DWORD tick = GetTickCount();
	if (tick - spawn_start > ITEM_SPAWN_TIME)
	{
		spawn_start = 0;
		isActive = false;
	}
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (ny != 0) vx = vy = 0;
	}
	if (x <= limit_left || x >= limit_right)
	{
		vx = -vx;
	}
}

void SmallHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y;
	left = x;
	right = x + SMALLHEART_BBOX_WIDTH;
	bottom = y + SMALLHEART_BBOX_HEIGHT;
}