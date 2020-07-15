#include "Enemy.h"

void CEnemy::Destroy()
{
	isActive = 0;
}


void CEnemy::Damage(int dmg)
{
	hp -= dmg;
	if (hp <= 0)
		this->Destroy();
}


CEnemy::~CEnemy()
{
}
