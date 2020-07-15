#include "StairTop.h"


void StairTop::Render()
{
	RenderBoundingBox();
}

void StairTop::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + STAIR_BBOX_WIDTH;
	bottom = top + STAIR_BBOX_HEIGHT;
}

StairTop::~StairTop()
{
}
