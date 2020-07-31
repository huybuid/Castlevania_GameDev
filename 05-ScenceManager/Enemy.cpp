#include "Enemy.h"

void CEnemy::Destroy()
{
	isActive = 0;
}


void CEnemy::Damage(int dmg)
{
	if (isDamaged) return;
	hp -= dmg;

	if (hp <= 0)
		this->Destroy();
	else
	{
		isDamaged = true;
		damage_start = GetTickCount();
		if (freeze_start == 0)
		{
			Freeze(DAMAGE_FREEZE_TIME);
		}
	}
}

void CEnemy::Freeze(DWORD time)
{
	freeze_time = time;
	freeze_start = GetTickCount();
}


CEnemy::~CEnemy()
{
}
