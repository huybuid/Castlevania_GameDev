#pragma once
#include "Weapon.h"

#define WHIP_LV1		0
#define WHIP_LV2		1
#define WHIP_LV3		2

#define WHIP_STATE_DEACTIVATE		0
#define WHIP_STATE_ATTACK			1

#define WHIP_ANI_CYCLE			100
#define WHIP_DAMAGE	2

#define WHIP_BACK_POSITION_LEFT 0
#define WHIP_BACK_POSTION_RIGHT 0
#define WHIP_FRONT_POSITION_LEFT 0
#define WHIP_FRONT_POSTION_RIGHT 0

#define WHIP_GAP 10
#define WHIP_SPRITES_HEIGHT	16
#define WHIP_SPRITES_WIDTH	112

#define WHIP_X_BBOX	50
#define WHIP_LONG_BBOX_WIDTH	48
#define WHIP_SHORT_BBOX_WIDTH	32
#define WHIP_BBOX_HEIGHT	6

#define WHIP_X_FRAMEDISTANCE 40

#define WHIP_ATTACK_TIME	300



class Whip :
	public CWeapon
{
public:
	bool isAttack;
	bool isHit;
	int level;
	DWORD attack_start;
public:
	Whip() :CWeapon()
	{
		isHit = false;
		isAttack = false;
		level = 0;
		attack_start = 0;
		SetAnimationSet(CAnimationSets::GetInstance()->Get(3));
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	//void ResetAttackState();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void SetFrame(int n) { animation_set->at(n)->SetCurrentFrame(); }
	void StartAttackSequence() {
		isHit = false;
		isAttack = 1; attack_start = GetTickCount();
	}
	virtual int GetDamage() { if (level < 1) return WHIP_DAMAGE; return WHIP_DAMAGE + 1; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Whip() { };
};

