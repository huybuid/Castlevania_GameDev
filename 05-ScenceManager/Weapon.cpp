#include "Weapon.h"

void CWeapon::CalcPotentialObjectsOverlapsed(vector<LPGAMEOBJECT> *coObjects,
	vector<LPGAMEOBJECT> &coResults)
{
	float tl, tt, tr, tb; //whip's coordinates
	this->GetBoundingBox(tl, tt, tr, tb);
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!coObjects->at(i)->isAttackable) continue; //if we can't attack object then continue
		float l, t, r, b;
		coObjects->at(i)->GetBoundingBox(l, t, r, b);
		// If one rectangle is on left side of other 
		if (tl >= r || l >= tr)
			continue;

		// If one rectangle is above other 
		if (tt >= b || t >= tb)
			continue;
		else
			coResults.push_back(coObjects->at(i));
	}
}

CWeapon::CWeapon() : CGameObject()
{
	//Set all bools to false
	isEnemy = false;
	isAttackable = false;
	isCollidable = false;
	isInteractive = false;
}


CWeapon::~CWeapon()
{
}
