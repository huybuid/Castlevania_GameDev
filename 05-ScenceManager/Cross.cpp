#include "Cross.h"

Cross::~Cross()
{
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);

}

void Cross::Render()
{
	int alpha = 255;
	animation_set->at(0)->Render(x, y, nx, alpha);
}

void Cross::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CROSS_BBOX_WIDTH;
	bottom = y + CROSS_BBOX_HEIGHT;
} 