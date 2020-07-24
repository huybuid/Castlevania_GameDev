#include "WeaponUpgrade.h"

void WeaponUpgrade::Render()
{
	if (!isActive) return;
	int alpha = 255;
	animation_set->at(type)->Render(x, y, nx, alpha);
}
