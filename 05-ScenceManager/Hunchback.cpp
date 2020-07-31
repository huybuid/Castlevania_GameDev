#include "Hunchback.h"
#include "PlayScence.h"
void Hunchback::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	float simon_x, simon_y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(simon_x, simon_y);
	if (tick - stop_time > HUNCHBACK_STOP_TIME && stop_time > 0)
	{
		if (next_nx == 0)
		{
			if (x < simon_x)
				nx = 1;
			else nx = -1;
		}
		else
		{
			nx = next_nx;
		}
		SetState(HUNCHBACK_STATE_JUMP);
	}
	vy += HUNCHBACK_GRAVITY * dt;
	CGameObject::Update(dt);
	if (state == HUNCHBACK_STATE_IDLE && stop_time ==0)
	{
		if (nx > 0)
		{
			if (simon_x < trigger)
				stop_time = GetTickCount();
		}
		else
		{
			if (simon_x > trigger)
				stop_time = GetTickCount();
		}
	}
	else
	{
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

			next_nx = nx;
			if (ny < 0 || nx != 0)
				SetState(HUNCHBACK_STATE_IDLE);
		}
	}
}

void Hunchback::Render()
{
	if (!isActive) return;
	if (freeze_start == 0)
		animation_set->at(state)->Render(x, y, nx);
	else animation_set->at(state)->FreezeRender(x, y, nx);
}

void Hunchback::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + HUNCHBACK_BBOX_WIDTH;
	bottom = y + HUNCHBACK_BBOX_HEIGHT;
}

Hunchback::~Hunchback()
{
}

void Hunchback::SetState(int s)
{
	int random = rand() % 2;
	state = s;
	switch (state)
	{
	case HUNCHBACK_STATE_JUMP:
		if (random == 0)
		{
			//Jump high
			vx = nx * HUNCHBACK_JUMPHIGH_SPEEDX;
			vy = -HUNCHBACK_JUMPHIGH_SPEEDY;
		}
		else
		{
			//Jump low
			vx = nx * HUNCHBACK_JUMPLOW_SPEEDX;
			vy = -HUNCHBACK_JUMPLOW_SPEEDY;
		}
		stop_time = 0;
		break;
	case HUNCHBACK_STATE_IDLE:
		vx = 0;
		vy = 0;
		if (stop_time == 0)
		stop_time = GetTickCount();
		break;
	default:
		break;
	}
}
