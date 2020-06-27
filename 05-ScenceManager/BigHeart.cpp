#include "BigHeart.h"

void BigHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	CItem::GetBoundingBox(left,top,right,bottom);
	right = x + HEART_BBOX_WIDTH;
	bottom = y + HEART_BBOX_HEIGHT;
}
