#include "StairBottom.h"

void StairBottom::Render()
{
	//RenderBoundingBox();
}

void StairBottom::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + STAIR_BBOX_WIDTH;
	bottom = top + STAIR_BBOX_HEIGHT;
}


StairBottom::~StairBottom()
{
}
