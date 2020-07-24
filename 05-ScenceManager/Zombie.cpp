#include "Zombie.h"


void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD tick = GetTickCount();
	vy += ZOMBIE_GRAVITY * dt;
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
		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny < 0)
		{
			vy = 0;
			vx = this->nx * ZOMBIE_SPEEDX;
		}
	}
}

void Zombie::Render()
{
	if (!isActive) return;
	animation_set->at(1)->Render(x, y, nx);
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

Zombie::~Zombie()
{
}
