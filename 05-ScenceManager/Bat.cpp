#include "Bat.h"
#include "PlayScence.h"

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	if (state == BAT_STATE_IDLE)
	{
		CGameObject *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if ((simon->y <= this->y + BAT_TRIGGER_Y) && (simon->x <= this->x + BAT_TRIGGER_X && simon->x >= this->x))
		{
			SetState(BAT_STATE_FLY);
		}
	}
	if (state == BAT_STATE_FLY)
	{
		x += dx;
		if (y + dy <= start_y + BAT_TRIGGER_Y + 8)
			y += dy;
		else
		{
			y = start_y + BAT_TRIGGER_Y + 8;
			vy = 0;
		}
	}
}

void Bat::Render()
{
	if (!isActive) return;
	if (freeze_start == 0)
	animation_set->at(state)->Render(x, y, nx);
	else animation_set->at(state)->FreezeRender(x, y, nx);
}

void Bat::SetState(int s)
{
	state = s;
	if (state == BAT_STATE_FLY)
	{
		vx = nx * BAT_SPEED_X;
		vy = BAT_SPEED_Y;
	}
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}



Bat::~Bat()
{
}
