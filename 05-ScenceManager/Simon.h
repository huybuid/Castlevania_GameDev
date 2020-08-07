#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Whip.h"
#include "define.h"

#define SIMON_WALKING_SPEED		0.07f 
#define SIMON_STAIR_SPEED		0.05f
#define SIMON_JUMP_SPEED_Y		0.23f
#define SIMON_HURT_SPEED		0.2f
#define SIMON_JUMP_GRAVITY		0.0007f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_MAX_HP			16

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING			10
#define SIMON_STATE_ATTACKING		20
#define SIMON_STATE_DUCKING			30
#define SIMON_STATE_DUCKATK			40
#define SIMON_STATE_JUMP			50
#define SIMON_STATE_HURT			60
#define SIMON_STATE_STAIRIDLE		70
#define SIMON_STATE_STAIRATK		80
#define SIMON_STATE_STAIRCLIMB		90
#define SIMON_STATE_DIE				9900

#define SIMON_ANI_IDLE				0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_ATTACKING			2
#define SIMON_ANI_DUCKING			3
#define SIMON_ANI_DUCKATK			4
#define SIMON_ANI_JUMP				5
#define SIMON_ANI_HURT				6
#define SIMON_ANI_STAIRUPIDLE		7
#define SIMON_ANI_STAIRUP			8
#define SIMON_ANI_STAIRUPATK		9
#define SIMON_ANI_STAIRDOWNIDLE		10
#define SIMON_ANI_STAIRDOWN			11
#define SIMON_ANI_STAIRDOWNATK		12
#define SIMON_ANI_DIE				13

#define SIMON_WEAPON_NONE			0
#define SIMON_WEAPON_AXE			1
#define SIMON_WEAPON_CROSS			2
#define SIMON_WEAPON_DAGGER			3
#define SIMON_WEAPON_HOLYWATER		4
#define SIMON_WEAPON_STOPWATCH		5

#define SIMON_IDLE_BBOX_WIDTH		16
#define SIMON_STANDING_BBOX_HEIGHT	30

#define SIMON_DUCKING_BBOX_WIDTH	16
#define SIMON_DUCKING_BBOX_HEIGHT	22

#define SIMON_UNTOUCHABLE_TIME	3000
#define SIMON_ATTACK_TIME		350
#define SIMON_JUMP_TIME			400
#define SIMON_HURT_TIME			400

#define TARGET_X_NaN	-9999 //because Simon will never reach this x cordinate, this can be an indicator for NaN value 

class CSimon :
	public CGameObject
{
public:
	int level; //indicates whip level
	int weapon_indicator, weapon_level; //indicates which weapon Simon is currently using
	int heart; // "bullets" for weapons
	int hp;
	bool isJump, isFall;
	bool isAttack, isWeaponAttack=false;
	bool isDuck;
	bool isHurt;
	bool isOnStairTop, isOnStairBottom, isWalkingtoStair = false;
	DWORD untouchable_start, attack_start, jump_start, hurt_start;

	Whip *whip;

	float start_x;			// initial position of Simon at scene
	float start_y;

	float target_x = TARGET_X_NaN; // target x for AutoWalk function
	float stair_nx, stair_ny;
public:
	CSimon(float x, float y, int nx, int state = 0, int lvl = 0, int h = 5, int current_hp = 16, int wp = 0, int wp_lvl = 0);
	CSimon(CSimon *s);
	CSimon() :CGameObject() { 
		this->animation_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_SIMON); 
		whip = new Whip();
		switch (CGame::GetInstance()->GetCurrentSceneNo())
		{
		case 1:
			start_x = STAGE_1_X;
			start_y = STAGE_1_Y;
			break;
		case 2:
			start_x = STAGE_2_X;
			start_y = STAGE_2_Y;
			break;
		case 3:
			start_x = STAGE_3_X;
			start_y = STAGE_3_Y;
			break;
		case 4:
			start_x = STAGE_4_X;
			start_y = STAGE_4_Y;
			break;
		case 5:
			start_x = STAGE_5_X;
			start_y = STAGE_5_Y;
			break;
		case 6:
			start_x = STAGE_6_X;
			start_y = STAGE_6_Y;
			break;
		}
	};
	~CSimon() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void ResetAttackState();
	void SetLevel(int l) { level = l; }

	void StartUntouchable() { 
		isHurt = 1; 
		untouchable_start = GetTickCount();
	}
	void StartAttackSequence(bool isWhipAtk);

	void Reset(float reset_x, float reset_y, int nx = 0, int state = 0);
	void HardReset();
	void SetWeapon(int indicator);

	void Walk(bool isUp);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

