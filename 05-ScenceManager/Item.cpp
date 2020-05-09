#include "Item.h"

void CItem::Render()
{
	if (!isActive) return;  //TEMPORARY
	int alpha = 255;
	animation_set->at(0)->Render(x, y, nx, alpha);
	//RenderBoundingBox();
}

void CItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
}
