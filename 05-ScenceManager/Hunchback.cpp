#include "Hunchback.h"


void Hunchback::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Hunchback::Render()
{
}

void Hunchback::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + HUNCHBACK_BBOX_WIDTH;
	bottom = y + HUNCHBACK_BBOX_HEIGHT;
}

Hunchback::~Hunchback()
{
}
