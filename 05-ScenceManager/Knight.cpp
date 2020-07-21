#include "Knight.h"



void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (x <= limit_l || x >= limit_r)
	{
		if (x <= limit_l) x = limit_l;
		else x = limit_r;
		nx = -nx;
		vx = nx * KNIGHT_SPEED_X;
	}
}

void Knight::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x,y,nx);
}

void Knight::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + KNIGHT_BBOX_WIDTH;
	bottom = y + KNIGHT_BBOX_HEIGHT;
}

Knight::~Knight()
{
}
