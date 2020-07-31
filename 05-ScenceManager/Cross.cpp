#include "Cross.h"
#include "PlayScence.h"
#include "Game.h"
#include "Enemy.h"


Cross::~Cross()
{
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if ((abs(x - origin_x) > CROSS_TURNBACK_X) && (state == CROSS_STATE_START))
	{
		SetState(CROSS_STATE_TURN);
	}
	if (state == CROSS_STATE_TURN)
	{
		vx += -origin_nx* CROSS_SPEED_TURNBACK * dt;
		if (vx*nx < 0)
			nx = -nx;
		if (abs(vx) > CROSS_SPEED_X)
		{
			SetState(CROSS_STATE_BACK);
		}
	}
	if (isHitWall())
	{
		if (!isChangedDirection)
			SetState(CROSS_STATE_BACK);
		else
			isActive = false;
	}
	if (state == CROSS_STATE_BACK)
	{
		LPCOLLISIONEVENT simon_e = AABB(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
		if (simon_e->t > 0 && simon_e->t <= 1)
		{
			isActive = false;
		}
	}
	vector<LPCOLLISIONEVENT> coResults;
	coResults.clear();
	vector<LPGAMEOBJECT> *enProjectiles = &((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->enemies_projectiles;
	CalcPotentialObjectsOverlapsed(coObjects, coResults);
	CalcPotentialObjectsOverlapsed(enProjectiles, coResults);
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

void Cross::Render()
{
	if (!isActive) return;
	int alpha = 255;
	animation_set->at(0)->Render(x, y, nx, alpha);
	//RenderBoundingBox();
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