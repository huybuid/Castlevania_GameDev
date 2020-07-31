#include "Simon.h"
#include "Game.h"
#include "Scence.h"
#include "Portal.h"
#include "Animations.h"
#include "GameObject.h"
#include "Item.h"
#include "PlayScence.h"
#include "StairTop.h"
#include "StairBottom.h"
#include "Platform.h"
#include "WeaponList.h"
#include "Utils.h"
#include "Grid.h"
#include "Bat.h"
#include "Raven.h"

CSimon::CSimon(float x, float y, int nx, int state, int lvl, int h, int current_hp, int wp, int wp_lvl) : CSimon()
{
	start_x = x;
	start_y = y;
	this->nx = nx;
	this->x = x;
	this->y = y;
	level = lvl;
	SetState(state);
	heart = h;
	hp = current_hp;
	weapon_indicator = wp;
	weapon_level = wp_lvl;
}

CSimon::CSimon(CSimon * s):CSimon()
{
	level = s->level;
	heart = s->heart;
	hp = s->hp;
	if (s->state == SIMON_STATE_STAIRCLIMB)
	{
		stair_nx = s->stair_nx;
		stair_ny = s->stair_ny;
	}
	weapon_indicator = s->weapon_indicator;
	weapon_level = s->weapon_level;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	if (state != SIMON_STATE_STAIRATK && state != SIMON_STATE_STAIRIDLE && state != SIMON_STATE_STAIRCLIMB)
	{
		if ((isJump || isHurt) && !isFall)
			vy += SIMON_JUMP_GRAVITY * dt;
		else vy += SIMON_GRAVITY * dt;
	}
	CGameObject::Update(dt);
	DWORD tick = GetTickCount();
	// reset untouchable timer if untouchable time has passed
	if (tick - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		isHurt = 0;
	}
	if (tick - hurt_start > SIMON_HURT_TIME && hurt_start > 0)
	{
		hurt_start = 0;
		isFall = true;
	}
	// reset attack if attack time has passed
	if (tick - attack_start > SIMON_ATTACK_TIME && attack_start > 0)
	{
		if (isWeaponAttack)
		{
			switch (weapon_indicator)
			{
			case SIMON_WEAPON_AXE:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new Axe(x + 8, y, nx));
				break;
			case SIMON_WEAPON_DAGGER:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new Dagger(x + 8, y, nx));
				break;
			case SIMON_WEAPON_CROSS:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new Cross(x + 8, y, nx));
				break;
			case SIMON_WEAPON_HOLYWATER:
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.push_back(new HolyWater(x + 12, y, nx));
				break;
			default:
				break;
			}
		}
		isAttack = 0;
		attack_start = 0;
		ResetAttackState();
	}
	if ((tick - jump_start > SIMON_JUMP_TIME) && (jump_start > 0))
	{
		jump_start = 0;
		isFall = true;
		if (!isAttack)
		{
			y -= 4;
		}
	}
	vector<LPCOLLISIONEVENT> inEvents;	//Interaction (with items) Events
	vector<LPGAMEOBJECT> *inObjects = &((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->items;
	inEvents.clear();
	CalcPotentialInteractions(inObjects, inEvents);
	CalcPotentialInteractions(coObjects, inEvents);
	vector<LPCOLLISIONEVENT> enEvents; //Interaction (with enemies) Events
	if (isOnStairTop || isOnStairBottom)
	{
		if (GetState() == SIMON_STATE_WALKING && target_x != TARGET_X_NaN && isWalkingtoStair)
		{
			if (nx <= 0) //Simon facing left
			{
				if (x+8 <= target_x)
				{
					x = target_x-8;
					nx = -stair_ny*stair_nx;
					SetState(SIMON_STATE_STAIRIDLE);
					isWalkingtoStair = false;
				}
			}
			else
			{
				if (x+8 >= target_x)
				{
					x = target_x-8;
					nx = -stair_ny*stair_nx;
					SetState(SIMON_STATE_STAIRIDLE);
					isWalkingtoStair = false;
				}
			}
		}
	}
	// Simple fall down
	

	vector<LPCOLLISIONEVENT> coEvents;	//Collision Events
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	if (state != SIMON_STATE_STAIRATK && state != SIMON_STATE_STAIRIDLE && state != SIMON_STATE_STAIRCLIMB)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}


	// Brick collision process
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		isOnStairBottom = false;
		isOnStairTop = false;

		if (!isJump && (tick - hurt_start > SIMON_HURT_TIME && hurt_start > 0)) 
			isFall = true;
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
		x += min_tx * dx + nx * 0.3f;	if (ny < 0)
			y += min_ty * dy + ny * 0.3f;
		else
			y += dy + ny * 0.3f;

		if (nx != 0) vx = 0;
		if (ny < 0)
		{
			isFall = false;
			if (isJump)
			{
				vx = 0;
				isJump = false;
				jump_start = 0;
				animation_set->at(SIMON_ANI_JUMP)->SetCurrentFrame();
			}
			if (animation_set->at(SIMON_ANI_HURT)->GetCurrentFrame() == 0)
			{
				SetState(SIMON_STATE_IDLE);
				animation_set->at(SIMON_ANI_HURT)->SetCurrentFrame();
			}
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//if collides with a moving platform
			if (dynamic_cast<Platform *>(e->obj))
			{
				x += e->obj->dx;
			}
		}
	}

	// Enemy collision process
	if (!isHurt)
	{
		vector<LPCOLLISIONEVENT> enEvents; //Enemy events
		enEvents.clear();
		CollisionsWithEnemies(coObjects, enEvents);
		if (enEvents.size() > 0)
		{
			ResetAttackState();
			if (state < SIMON_STATE_STAIRIDLE || state > SIMON_STATE_STAIRCLIMB)
			{
				nx = -enEvents[0]->nx;
				SetState(SIMON_STATE_HURT);
			}
			else
			{
				StartUntouchable();
			}
			hp -= 2;
			if (dynamic_cast<Bat *>(enEvents[0]->obj) || dynamic_cast<Raven *>(enEvents[0]->obj))
			{
				dynamic_cast<CEnemy *>(enEvents[0]->obj)->Destroy();
			}
		}
	}
	isOnStairBottom = false;
	isOnStairTop = false;
	//Items collision process
	if (inEvents.size()>0)
	for (UINT i = 0; i < inEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = inEvents[i];
		if (dynamic_cast<CItem *>(e->obj))
		{
			CItem *item = dynamic_cast<CItem *>(e->obj);
			item->Destroy();
			continue;
		}
		if (dynamic_cast<CPortal *>(e->obj))
		{
			CPortal *p = dynamic_cast<CPortal *>(e->obj);
			CGame::GetInstance()->SwitchScene(p->GetSceneId(),p->simon_x, p->simon_y, p->simon_nx, p->simon_state);
			continue;
		}
		if (dynamic_cast<StairTop *>(e->obj))
		{
			if (e->ny > 0)
			{
				target_x = e->obj->x;
				if (state < SIMON_STATE_STAIRIDLE || state > SIMON_STATE_STAIRCLIMB)
				{
					stair_nx = e->obj->nx;
					isOnStairTop = true;
				}
			}
			if (state == SIMON_STATE_STAIRCLIMB && e->obj->nx == stair_nx && stair_ny == -1)
			{
				SetState(SIMON_STATE_IDLE);
				x = target_x - 8;
			}
			continue;
		}
		if (dynamic_cast<StairBottom *>(e->obj))
		{
			if (e->ny < 0)
			{
				target_x = e->obj->x;
				if (state < SIMON_STATE_STAIRIDLE || state > SIMON_STATE_STAIRCLIMB)
				{
					stair_nx = e->obj->nx;
					isOnStairBottom = true;
				}
			}
			if (state == SIMON_STATE_STAIRCLIMB && e->obj->nx == stair_nx && stair_ny == 1)
			{
				SetState(SIMON_STATE_IDLE);
				y-=dy; //pull up Simon by to avoid falling through bricks
				x = target_x - 8;
			}
			continue;
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
	animation_set->at(SIMON_ANI_STAIRUPATK)->SetCurrentFrame();
	animation_set->at(SIMON_ANI_STAIRDOWNATK)->SetCurrentFrame();
	if (state >= SIMON_STATE_STAIRIDLE && state <=SIMON_STATE_STAIRCLIMB)
	{
		SetState(SIMON_STATE_STAIRIDLE);
	}
	else
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
	if (isHurt) alpha = 128;

	if (state == SIMON_STATE_DIE) {
		ani = SIMON_ANI_DIE;
	}
	else if (state == SIMON_STATE_HURT) {
		ani = SIMON_ANI_HURT;
	}
	else 
	{
		if (state >= SIMON_STATE_STAIRIDLE && state <= SIMON_STATE_STAIRCLIMB)
		{
			if (vx == 0)
			{
				if (isAttack)
				{
					if (stair_ny < 0)
						ani = SIMON_ANI_STAIRUPATK;
					else ani = SIMON_ANI_STAIRDOWNATK;
				}
				else
				{
					if (stair_ny < 0)
					{
							ani = SIMON_ANI_STAIRUPIDLE;
					}
					else ani = SIMON_ANI_STAIRDOWNIDLE;
				}
			}
			else
			{
				if (stair_ny < 0)
					ani = SIMON_ANI_STAIRUP;
				else ani = SIMON_ANI_STAIRDOWN;
			}
		}
		else
		if (vx == 0)
		{
			//Attacking
			if (state == SIMON_STATE_ATTACKING || state==SIMON_STATE_DUCKATK || state==SIMON_STATE_STAIRATK) {
				if (state==SIMON_STATE_DUCKATK) ani = SIMON_ANI_DUCKATK;
				else	
					ani = SIMON_ANI_ATTACKING;
			}
			//Ducking----------------------------------
			else if (isDuck) {
				ani = SIMON_ANI_DUCKING;
			}
			//Jumping
			else if (isJump)
				ani = SIMON_ANI_JUMP;
			else {
				if (state == SIMON_STATE_WALKING) ani = SIMON_ANI_WALKING;
				else ani = SIMON_ANI_IDLE;
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
		jump_start = GetTickCount();
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		if (!isJump)
			vx = 0;
		if (prevstate == SIMON_STATE_STAIRCLIMB)
			vy = 0;
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
				y -= 4;
		}
		else
			vx = 0;
	break;
	case SIMON_STATE_WALKING:
		vx = SIMON_WALKING_SPEED * nx;
		break;
	case SIMON_STATE_STAIRATK:
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_STAIRCLIMB:
		if (stair_ny > 0)
		{
			nx = -stair_nx;
		}
		else
		{
			nx = stair_nx;
		}
		vx = nx * SIMON_STAIR_SPEED;
		vy = stair_ny * SIMON_STAIR_SPEED;
		break;
	case SIMON_STATE_STAIRIDLE:
		vx = 0;
		vy = 0;
		dy = 0;
		dx = 0;
		break;
	case SIMON_STATE_HURT:
		StartUntouchable();
		if (prevstate < SIMON_STATE_STAIRIDLE || prevstate > SIMON_STATE_STAIRCLIMB)
		{
			vx = -nx * SIMON_STAIR_SPEED;
			vy = -SIMON_HURT_SPEED;
			hurt_start = untouchable_start;
		}
		break;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x+8;
	top = y;

	if (isDuck || (isJump && !isFall))
	{
		right = left + SIMON_DUCKING_BBOX_WIDTH;
		bottom = y + SIMON_DUCKING_BBOX_HEIGHT;
	}
	else
	{
		right = left + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_STANDING_BBOX_HEIGHT;
	}
}

void CSimon::StartAttackSequence(bool isWhipAtk)
{
		isAttack = 1;
		attack_start = GetTickCount();
		int current_weapon_count = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->weapons.size();
		if (isWhipAtk || current_weapon_count >= weapon_level || weapon_indicator == SIMON_WEAPON_NONE || weapon_indicator == SIMON_WEAPON_STOPWATCH || heart<=0)
			whip->SetState(WHIP_STATE_ATTACK);
		else
		{
			isWeaponAttack = true;
			heart--;
		}
		if (weapon_indicator == SIMON_WEAPON_STOPWATCH && !isWhipAtk)
		{
			if (heart >= 5)
			{
				CGrid::GetInstance()->StopTime();
				heart -= 5;
			}
		}
		if (state >= SIMON_STATE_STAIRIDLE && state <= SIMON_STATE_STAIRCLIMB)
		{
			SetState(SIMON_STATE_STAIRATK);
			return;
		}
		if (isDuck)
			SetState(SIMON_STATE_DUCKATK);
		else
			SetState(SIMON_STATE_ATTACKING);
}

/*
	Reset SIMON status to the beginning state of a scene
*/
void CSimon::Reset(float reset_x, float reset_y, int nx, int state)
{
	SetState(state);
	start_x = reset_x;
	start_y = reset_y;
	this->nx = nx;
	SetPosition(reset_x, reset_y);
}

void CSimon::HardReset()
{
	Reset(start_x, start_y);
	SetLevel(0);
	weapon_indicator = SIMON_WEAPON_NONE;
	hp = SIMON_MAX_HP;
	heart = 5;
	weapon_level = 0;
}

void CSimon::SetWeapon(int indicator)
{
	weapon_indicator = indicator;
	weapon_level = 1;
}

void CSimon::Walk(bool isUp)
{
	isWalkingtoStair = true;
	if (target_x < x)
		nx = -1;
	else  if (target_x > x) nx = 1;
	else  if (isUp) nx = -stair_nx;
	else nx = stair_nx;
	SetState(SIMON_STATE_WALKING);
}


