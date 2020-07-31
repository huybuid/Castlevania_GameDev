#include "Whip.h"
#include "Simon.h"
#include "Game.h"
#include "FirePillar.h"
#include "PlayScence.h"
#include "Scence.h"
//#include "FirePilar.h"

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	//CGameObject::Update(dt);
	CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (GetState()!=WHIP_STATE_ATTACK) return;
	DWORD tick = GetTickCount();
	//Update whip's position according to Simon's
	this->level = simon->level;
	this->nx = simon->nx;
	this->x = simon->x - WHIP_X_FRAMEDISTANCE;
	this->y = simon->y;

	if (tick - attack_start > 200 && tick - attack_start <= 300)
	{
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
				if (dynamic_cast<CEnemy *>(e->obj)) //if object is FirePillar
				{
					CEnemy *target = dynamic_cast<CEnemy *>(e->obj);
					target->Damage(dmg);
				}
			}
		}
	}
	if (tick - attack_start > 300)
	{
		if (isAttack) //Is the attack button still down?
		{
			StartAttackSequence();
		}
	}
}

void Whip::Render() {
	if (!isAttack) return;
	int alpha = 255;
	animation_set->at(level)->Render(x, y, nx, alpha);
	//RenderBoundingBox();
}

void Whip::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case WHIP_STATE_DEACTIVATE:
		isAttack = false;
		attack_start = 0;
		animation_set->at(level)->SetCurrentFrame();
		break;
	case WHIP_STATE_ATTACK:
		StartAttackSequence();
		isAttack = true;
		break;
	}

}


void Whip::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	top = y + WHIP_GAP;
	bottom = top + WHIP_BBOX_HEIGHT;
	if (nx <= 0) //facing left
	{
		right = x + WHIP_X_BBOX;
		if (level < 2) left = right - WHIP_SHORT_BBOX_WIDTH;
		else left = x + 2;
	}
	else //facing right
	{
		left = x - WHIP_X_BBOX + WHIP_SPRITES_WIDTH;
		if (level < 2)
		{
			right = left + WHIP_SHORT_BBOX_WIDTH;
		}
		else
		{
			right = left + WHIP_LONG_BBOX_WIDTH;
		}

	}
}