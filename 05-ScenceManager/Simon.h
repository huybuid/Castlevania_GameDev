#pragma once
#include "GameObject.h"
#include "Whip.h"

#define SIMON_WALKING_SPEED		0.07f 
#define SIMON_JUMP_SPEED_Y		0.2f
#define SIMON_JUMP_DEFLECT_SPEED 0.1f
#define SIMON_JUMP_GRAVITY		0.0006f
#define SIMON_GRAVITY			0.001f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_MAX_HP			16

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING			100
#define SIMON_STATE_ATTACKING		300
#define SIMON_STATE_DUCKING			500
#define SIMON_STATE_DUCKATK			700
#define SIMON_STATE_JUMP			900
#define SIMON_STATE_DIE				9900

#define SIMON_ANI_IDLE				0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_ATTACKING			2
#define SIMON_ANI_DUCKING			3
#define SIMON_ANI_DUCKATK			4
#define SIMON_ANI_JUMP				5

#define SIMON_ANI_DIE				20

#define SIMON_WEAPON_NONE			0
#define SIMON_WEAPON_AXE			1
#define SIMON_WEAPON_CROSS			2
#define SIMON_WEAPON_DAGGER			3
#define SIMON_WEAPON_HOLYWATER		4
#define SIMON_WEAPON_STOPWATCH		5

#define SIMON_IDLE_BBOX_WIDTH		16
#define SIMON_STANDING_BBOX_HEIGHT	32

#define SIMON_DUCKING_BBOX_WIDTH	16
#define SIMON_DUCKING_BBOX_HEIGHT	24

#define SIMON_UNTOUCHABLE_TIME	5000
#define SIMON_ATTACK_TIME		350

class CSimon :
	public CGameObject
{
public:
	int level; //indicates whip level
	int weapon_indicator; //indicates which weapon Simon is currently using
	int heart;
	bool untouchable;
	int hp;
	int weapon_level, current_weapon_count=0;
	bool isJump;
	bool isAttack, isWeaponAttack=false;
	bool isDuck;
	DWORD untouchable_start;
	DWORD attack_start;

	Whip *whip;

	float start_x;			// initial position of Simon at scene
	float start_y;
public:
	CSimon(float x = 0.0f, float y = 0.0f, float nx = 0);
	~CSimon() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void ResetAttackState();
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartAttackSequence(bool isWhipAtk);

	void Reset(float reset_x, float reset_y, float nx = 0);
	void HardReset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

