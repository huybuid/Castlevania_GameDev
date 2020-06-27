#include "Simon.h"
#include "Game.h"
#include "Goomba.h"
#include "Scence.h"
#include "Portal.h"
#include "Animations.h"
#include "GameObject.h"
#include "Item.h"
#include "PlayScence.h"
#include "define.h"
#include "Dagger.h"
#include "Axe.h"
#include "Cross.h"
#include "HolyWater.h"

CSimon::CSimon(float x, float y) : CGameObject()
{
	level = 0;
	untouchable = 0;
	isJump = 0;
	isAttack = 0;
	isDuck = 0;
	SetState(SIMON_STATE_IDLE);
	heart = 5;
	hp = SIMON_MAX_HP;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	this->animation_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_SIMON);
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_JUMP_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;	//Collision Events
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPCOLLISIONEVENT> inEvents;	//Interaction (with items) Events
	vector<LPGAMEOBJECT> *inObjects = &((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->items;
	coEvents.clear();
	inEvents.clear();
	// turn off collision when dead 
	if (state != SIMON_STATE_DIE || untouchable)
		CalcPotentialCollisions(coObjects, coEvents);
	CalcPotentialInteractions(inObjects, inEvents);
	// reset untouchable timer if untouchable time has passed
	DWORD tick = GetTickCount();
	if (tick - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (tick - attack_start > SIMON_ATTACK_TIME && attack_start>0)
	{
		if (isWeaponAttack)
		{

			switch (weapon_indicator)
			{
			case SIMON_WEAPON_AXE:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new Axe(x+8, y, nx));
				break;
			case SIMON_WEAPON_DAGGER:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new Dagger(x+8, y, nx));
				break;
			case SIMON_WEAPON_CROSS:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new Cross(x+8, y, nx));
				break;
			case SIMON_WEAPON_HOLYWATER:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new HolyWater(x+8, y, nx));
			default:
				break;
			}
		}
		isAttack = 0;
		attack_start = 0;
		ResetAttackState();
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back SIMON if collides with a moving objects, what if SIMON is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.1f;
		if (ny < 0)
			y += min_ty * dy + ny * 0.1f;
		else
			y += dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny < 0)
		{
			if (isJump)
			{
				vx = 0;
				isJump = false;
				animation_set->at(SIMON_ANI_JUMP)->SetCurrentFrame();
			}
			vy = 0;
		}
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//if collides with a portal
			if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}
	if (inEvents.size()>0)
	for (UINT i = 0; i < inEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = inEvents[i];
		if (dynamic_cast<CItem *>(e->obj))
		{
			CItem *item = dynamic_cast<CItem *>(e->obj);
			item->Destroy();
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	for (UINT i = 0; i < inEvents.size(); i++) delete inEvents[i];

}

void CSimon::ResetAttackState()
{
	whip->SetState(WHIP_STATE_DEACTIVATE);
	animation_set->at(SIMON_ANI_DUCKATK)->SetCurrentFrame();
	animation_set->at(SIMON_ANI_ATTACKING)->SetCurrentFrame();
	if (GetState() == SIMON_STATE_ATTACKING || !isDuck)
	{
		SetState(SIMON_STATE_IDLE);
	}
	else
	{
		SetState(SIMON_STATE_DUCKING);
	}
	isWeaponAttack = false;
}

void CSimon::Render() {
	int ani;
	int alpha = 255;
	if (untouchable) alpha = 128;
	if (state == SIMON_STATE_DIE) {
		ani = SIMON_ANI_DIE;
	}
	else {
		//stand still => velocity x (vx = 0)

		//Idle--------------------------------------
		if (vx == 0)
		{
			//Attacking
			if (state == SIMON_STATE_ATTACKING || state==SIMON_STATE_DUCKATK) {
				if (state==SIMON_STATE_DUCKATK) ani = SIMON_ANI_DUCKATK;
				else ani = SIMON_ANI_ATTACKING;
			}
			//Ducking----------------------------------
			else if (isDuck) {
				ani = SIMON_ANI_DUCKING;
			}
			//Jumping
			else if (isJump)
				ani = SIMON_ANI_JUMP;
			else {
				ani = SIMON_ANI_IDLE;
			}
		}

		//Walking--------------------------------
		else
		{
			//Moving
			if (isJump == true)
			{
				if (GetTickCount() - attack_start < SIMON_ATTACK_TIME && attack_start > 0) ani = SIMON_ANI_ATTACKING;
				else ani = SIMON_ANI_JUMP;
			}
			else  ani = SIMON_ANI_WALKING;
		}
	}
	animation_set->at(ani)->Render(x, y, nx, alpha);
	//RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	int prevstate = GetState();
	if (prevstate == SIMON_STATE_WALKING && prevstate!=state)
		animation_set->at(SIMON_ANI_WALKING)->SetCurrentFrame();
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_JUMP:
		// TODO: need to check if SIMON is *current* on a platform before allowing to jump again
		isJump = true;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		if (!isJump)
			vx = 0;
		isDuck = false;
		break;
	case SIMON_STATE_DUCKING:
		isDuck = true;
		if (prevstate!= SIMON_STATE_DUCKING && prevstate!= SIMON_STATE_DUCKATK)
			y += 8;
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_ATTACKING:
		if (isJump)
		{
			if (animation_set->at(SIMON_ANI_JUMP)->GetCurrentFrame() == 0)
				y -= 8;
		}
		else
			vx = 0;
	break;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x+8;
	top = y;

	if (!isDuck)
	{
		right = left + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_STANDING_BBOX_HEIGHT;
	}
	else
	{
		right = left + SIMON_DUCKING_BBOX_WIDTH;
		bottom = y + SIMON_DUCKING_BBOX_HEIGHT;
	}
}

void CSimon::StartAttackSequence(bool isWhipAtk)
{
		isAttack = 1;
		attack_start = GetTickCount();
		if (isWhipAtk || current_weapon_count >= weapon_level || weapon_indicator == SIMON_WEAPON_NONE || weapon_indicator == SIMON_WEAPON_STOPWATCH)
			whip->SetState(WHIP_STATE_ATTACK);
		else
		{
			isWeaponAttack = true;
		}
		if (weapon_indicator == SIMON_WEAPON_STOPWATCH)
		{
			//Stop time
		}
		if (isDuck)
			SetState(SIMON_STATE_DUCKATK);
		else SetState(SIMON_STATE_ATTACKING);
}

/*
	Reset SIMON status to the beginning state of a scene
*/
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CSimon::HardReset()
{
	Reset();
	SetLevel(0);
	weapon_indicator = SIMON_WEAPON_NONE;
	hp = SIMON_MAX_HP;
	heart = 5;
	weapon_level = 0;
}


