#include "Axe.h"

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CWeapon::Update(dt, coObjects);
	x += dx;
	y += dy;
	vy += AXE_GRAVITY *dt;
}

void Axe::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y, nx);
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	left = y + AXE_BBOX_HEIGHT;
}
