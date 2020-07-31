#include "Weapon.h"
#include "Enemy.h"
#include "Game.h"
#include "PlayScence.h"

void CWeapon::CalcPotentialObjectsOverlapsed(vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coResults)
{

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!coObjects->at(i)->isAttackable || !coObjects->at(i)->isActive ) continue; //if we can't attack object then continue
		LPCOLLISIONEVENT e;
		if (this->isAABB(coObjects->at(i)))
		{
			e = AABB(coObjects->at(i));
		}
		else
		{
			e = SweptAABBEx(coObjects->at(i));
		}
		if (e->t > 0 && e->t <= 1.0f)
			coResults.push_back(e);
		else
			delete e;
	}
}

bool CWeapon::isOutOfScreen(int obj_width, int obj_height)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (this->x <= cam_x || this->x + obj_width >= cam_x + SCREEN_WIDTH || this->y <=cam_y || this->y + obj_height >= cam_y + SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}

CWeapon::CWeapon() : CGameObject()
{
	//Set all bools to false
	isEnemy = false;
	isAttackable = false;
	isCollidable = false;
	isInteractive = false;
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//more codes to follow up
}


CWeapon::~CWeapon()
{
}
