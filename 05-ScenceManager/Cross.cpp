#include "Cross.h"
#include "PlayScence.h"
#include "Game.h"


Cross::~Cross()
{
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (isHitWall())
	{
		if (!isChangedDirection)
			ChangeDirection();
		else
			isActive = false;
	}
}

void Cross::Render()
{
	if (!isActive) return;
	int alpha = 255;
	animation_set->at(0)->Render(x, y, nx, alpha);
}

bool Cross::isHitWall()
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (this->x <= cam_x || this->x + CROSS_BBOX_WIDTH >= cam_x + SCREEN_WIDTH)
	{
		if (this->x <= cam_x)
			x = cam_x;
		else
			x = cam_x + SCREEN_WIDTH - CROSS_BBOX_WIDTH - 16;
		return true;
	}
	return false;
}

void Cross::ChangeDirection()
{
	vx = -vx;
	nx = -nx;
	isChangedDirection = true;
}

void Cross::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CROSS_BBOX_WIDTH;
	bottom = y + CROSS_BBOX_HEIGHT;
} 