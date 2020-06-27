#include "Dagger.h"

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CWeapon::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void Dagger::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y, nx);
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	left = y + DAGGER_BBOX_HEIGHT;
}
