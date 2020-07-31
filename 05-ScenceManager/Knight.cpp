#include "Knight.h"



void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD tick = GetTickCount();
	if (freeze_start > 0)
	{
		if (isDamaged)
		{
			if (tick - damage_start > DAMAGE_FREEZE_TIME)
			{
				isDamaged = false;
				damage_start = 0;
			}
		}
		if (tick - freeze_start > freeze_time)
		{
			freeze_start = 0;
			freeze_time = 0;
		}
		return;
	}
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
	if (freeze_start == 0)
		animation_set->at(state)->Render(x, y, nx);
	else animation_set->at(state)->FreezeRender(x, y, nx);
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
