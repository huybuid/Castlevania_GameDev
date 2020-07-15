#include "Axe.h"
#include "Enemy.h"
void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CWeapon::Update(dt, coObjects);
	x += dx;
	y += dy;
	vy += AXE_GRAVITY *dt;
	if (isOutOfScreen(AXE_BBOX_WIDTH, AXE_BBOX_HEIGHT))
	{
		isActive = false;
	}
	vector<LPCOLLISIONEVENT> coResults;
	coResults.clear();
	CalcPotentialObjectsOverlapsed(coObjects, coResults);
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

void Axe::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y, nx);
	//RenderBoundingBox();
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}
