#pragma once
#include "Enemy.h"
#include "Weapon.h"

#define BONE_1_SPEEDX	0.08f
#define BONE_1_SPEEDY	0.12f
#define BONE_2_SPEEDX	0.06f
#define BONE_2_SPEEDY	0.2f
#define BONE_3_SPEEDX	0.04f
#define BONE_3_SPEEDY	0.24f
#define BONE_GRAVITY	0.0005f

#define ANIMATION_SET_BONE 32

#define BONE_BBOX_WIDTH	16
#define BONE_BBOX_HEIGHT 16
class Bone :
	public CEnemy
{
public:
	Bone() :CEnemy() { hp = 1; }
	Bone(float x, float y, float n, int type):Bone() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BONE));
		SetPosition(x, y);
		nx = n;
		switch (type)
		{
		case 1:
			vx = nx * BONE_1_SPEEDX;
			vy = -BONE_1_SPEEDY;
			break;
		case 2:
			vx = nx * BONE_2_SPEEDX;
			vy = -BONE_2_SPEEDY;
			break;
		case 3:
			vx = nx * BONE_3_SPEEDX;
			vy = -BONE_3_SPEEDY;
			break;
		default:
			vx = nx * BONE_1_SPEEDX;
			vy = -BONE_1_SPEEDY;
			break;
		}
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Bone();
	bool isOutOfScreen(int obj_width, int obj_height);
};

