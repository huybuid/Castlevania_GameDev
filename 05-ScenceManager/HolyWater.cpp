#include "HolyWater.h"

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CWeapon::Update(dt, coObjects);
	x += dx;
	y += dy;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);
	if (GetState()==HOLYWATER_STATE_BOTTLE)
		vy += HOLYWATER_GRAVITY * dt;
}

void HolyWater::Render()
{
	if (!isActive) return;
	int alpha = 255;
	animation_set->at(state)->Render(x, y, nx, alpha);
}

void HolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	bottom = y + HOLYWATER_BBOX_Y;

}
