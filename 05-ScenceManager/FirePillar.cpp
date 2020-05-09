#include "FirePillar.h"
#include "PlayScence.h"
#include "BigHeart.h"
#include "Game.h"
void FirePillar::Render()
{
	if (!isActive) return;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void FirePillar::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + FIREPILLAR_BBOX_WIDTH;
	b = y + FIREPILLAR_BBOX_HEIGHT;
}

void FirePillar::Destroy()
{
	BigHeart *item = new BigHeart();
	item->SetPosition(this->x, this->y);
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->items.push_back(item);
	isActive = false;
}
