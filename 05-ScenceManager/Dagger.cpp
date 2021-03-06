#include "Dagger.h"
#include "Enemy.h"
#include "PlayScence.h"

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CWeapon::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (isOutOfScreen(DAGGER_BBOX_WIDTH, DAGGER_BBOX_HEIGHT))
	{
		isActive = false;
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
			if (dynamic_cast<CEnemy *>(e->obj))
			{
				CEnemy *target = dynamic_cast<CEnemy *>(e->obj);
				target->Damage(dmg);
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(target->x, target->y, 0));
				isActive = false;
			}
		}
	}
}

void Dagger::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y, nx);
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}
