#pragma once
#include "GameObject.h"
class CEnemy :
	public CGameObject
{
protected:
	int hp;
public:
	CEnemy() :CGameObject() { isCollidable = false; isEnemy = true; isAttackable = true; };
	int GetHp() { return hp; };
	void SetHp(int x) { hp = x; };
	virtual void Destroy() =0;
	void Damage(int dmg);
	~CEnemy();
};

