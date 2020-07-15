#include "Item.h"

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!isActive) return;
	CGameObject::Update(dt);
	vy += ITEM_GRAVITY * dt;
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
		if (ny != 0) vy = 0;
	}
}

void CItem::Render()
{
	if (!isActive) return;  //TEMPORARY
	int alpha = 255;
	animation_set->at(0)->Render(x, y, nx, alpha);
	//RenderBoundingBox();
}

void CItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 16;
}
