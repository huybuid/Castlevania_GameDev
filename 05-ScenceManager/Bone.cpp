#include "Bone.h"
#include "PlayScence.h"

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += BONE_GRAVITY * dt;
	x += dx;
	y += dy;
	//"illegal" use of isOutOfScreen
	if (isOutOfScreen(BONE_BBOX_WIDTH, BONE_BBOX_HEIGHT))
	{
		isActive = false;
	}
}

void Bone::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y, nx);
}

void Bone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y;
	left = x;
	bottom = y + BONE_BBOX_HEIGHT;
	right = x + BONE_BBOX_WIDTH;
}

bool Bone::isOutOfScreen(int obj_width, int obj_height)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (this->x <= cam_x || this->x + obj_width >= cam_x + SCREEN_WIDTH || this->y <= cam_y || this->y + obj_height >= cam_y + SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}

Bone::~Bone()
{
}
