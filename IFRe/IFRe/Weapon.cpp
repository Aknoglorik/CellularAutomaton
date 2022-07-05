#include "Weapon.h"

Weapon::Weapon()
{
	dmg = 10.f;
	distance_damage = 10.f;
	holder_size = 10.f;
	reload_time = 10.f;
	bullet_per_sec = 10.f;
	range = 10.f;
	armour_penetration = 10.f;
}

Weapon::~Weapon()
{
}
