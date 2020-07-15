#include "HolyWater.h"
#include "Enemy.h"
void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	DWORD tick = GetTickCount();
	if (GetState() == HOLYWATER_STATE_BOTTLE)
	{
		vy += HOLYWATER_GRAVITY * dt;

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

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// how to push back SIMON if collides with a moving objects, what if SIMON is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx); 

			// block every object first!
			x += min_tx * dx + nx * 0.1f;
			y += min_ty * dy + ny * 0.4f;

			vx = 0;
			vy = 0;
			SetState(HOLYWATER_STATE_BURN);
			burn_time = GetTickCount();
		}
	}
	else
	{
		if (tick - burn_time > HOLYWATER_BURN_TIME && burn_time > 0)
		{
			animation_set->at(1)->SetCurrentFrame();
			isActive = false;
			burn_time = 0;
		}
	}
	vector<LPCOLLISIONEVENT> coResults;
	coResults.clear();
	CalcPotentialObjectsOverlapsed(coObjects, coResults);
	if (coResults.size() > 0) //
	{
		int dmg = GetDamage();
		for (UINT i = 0; i < coResults.size(); i++)
		{
			LPCOLLISIONEVENT e = coResults[i];
			if (dynamic_cast<CEnemy *>(e->obj)) //if object is FirePillar
			{
				CEnemy *target = dynamic_cast<CEnemy *>(e->obj);
				target->Damage(dmg);
			}
		}
	}
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
	right = (GetState() == HOLYWATER_STATE_BOTTLE) ? x + 8 : x + 16;
}
