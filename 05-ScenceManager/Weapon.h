#pragma once
#include "GameObject.h"

#define WEAPON_STATE_DEACTIVATE		0
#define WEAPON_STATE_ATTACK			1

#define WEAPON_DAMAGE_CYCLE	100
class CWeapon :
	public CGameObject
{
public:
	CWeapon();
	void CalcPotentialObjectsOverlapsed(vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> &coResults);
	~CWeapon();
};

