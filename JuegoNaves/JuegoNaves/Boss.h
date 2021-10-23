#pragma once

#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss(float x, float y, Game* game);
	Projectile* shootPlayer() override;
	void update() override;
	void tp();

	int tpTime;
};


