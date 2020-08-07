#include "Fireball.h"

void Fireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (isOutOfScreen(FIREBALL_BBOX_WIDTH, FIREBALL_BBOX_HEIGHT))
	{
		isActive = false;
	}
}

void Fireball::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y, nx);
}

void Fireball::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y;
	left = x;
	bottom = y + FIREBALL_BBOX_HEIGHT;
	right = x + FIREBALL_BBOX_WIDTH;
}

bool Fireball::isOutOfScreen(int obj_width, int obj_height)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (this->x <= cam_x || this->x + obj_width >= cam_x + SCREEN_WIDTH || this->y <= cam_y || this->y + obj_height >= cam_y + SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}

Fireball::~Fireball()
{
}

