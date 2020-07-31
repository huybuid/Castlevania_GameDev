#pragma once
#include "GameObject.h"

#define STOPWATCH_FREEZE_TIME	3000
#define DAMAGE_FREEZE_TIME	250

#define DEATH_FX	513
class CEnemy :
	public CGameObject
{
protected:
	LPANIMATION deathfx = CAnimations::GetInstance()->Get(DEATH_FX);
	int hp;
	bool isDamaged = false;
	DWORD damage_start = 0;
	DWORD freeze_time, freeze_start = 0;
public:
	CEnemy() :CGameObject() { isCollidable = false; isEnemy = true; isAttackable = true; };
	int GetHp() { return hp; };
	void SetHp(int x) { hp = x; };
	virtual void Destroy();
	void Damage(int dmg);
	void Freeze(DWORD time);
	~CEnemy();
};

