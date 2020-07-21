#include "MoneyPouch.h"

void MoneyPouch::Render()
{
	if (!isActive) return;
	animation_set->at(type)->Render(x, y, 0);
}
