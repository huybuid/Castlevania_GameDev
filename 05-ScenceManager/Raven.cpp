#include "Raven.h"
#include "PlayScence.h"

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	CGameObject *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (state == RAVEN_STATE_IDLE)
	{
		if (simon->x >= this->x - RAVEN_TRIGGER_X)
		{
			SetState(RAVEN_STATE_FLYDOWN);
		}
		return;
	}
	if (state == RAVEN_STATE_FLYDOWN)
	{
		x += dx;
		y += dy;
		if (y >= simon->y)
		{
			SetState(RAVEN_STATE_STRIKE);
		}
	}
	if (state == RAVEN_STATE_STRIKE)
	{
		if (simon->x < x) nx = -1;
		else nx = 1;
		vx += nx * RAVEN_ACCELARATION_SPEED * dt;
		if (vx >= RAVEN_SPEED_X) vx = RAVEN_SPEED_X;
		if (vx <= -RAVEN_SPEED_X) vx = -RAVEN_SPEED_X;
		x += dx;
	}
}

void Raven::Render()
{
	if (!isActive) return;
	int current_ani = (state == RAVEN_STATE_IDLE) ? 0 : 1;
	if (freeze_start == 0)
		animation_set->at(current_ani)->Render(x, y, nx);
	else animation_set->at(current_ani)->FreezeRender(x, y, nx);
}

void Raven::SetState(int s)
{
	state = s;
	switch (state)
	{
	case RAVEN_STATE_FLYDOWN:
		vx = nx * RAVEN_SPEED_X;
		vy = RAVEN_SPEED_Y;
		break;
	case RAVEN_STATE_STRIKE:
		vx = 0;
		vy = 0;
		break;
	default:
		break;
	}
}

void Raven::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + RAVEN_BBOX_WIDTH;
	bottom = y + RAVEN_BBOX_HEIGHT;
}

Raven::~Raven()
{
}
