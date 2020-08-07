#include "Enemy.h"
#include "PlayScence.h"
#include "HitFX.h"

void CEnemy::Destroy()
{
	float fx_x, fx_y;
	float t, l, r, b;
	GetBoundingBox(l, t, r, b);
	if (r - l < 16)
	{
		fx_x = x;
		fx_y = y + 2;
	}
	else
	{
		fx_x = x + 4;
		fx_y = y + 2;
	}
	isActive = 0;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(fx_x, fx_y, 1));
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
