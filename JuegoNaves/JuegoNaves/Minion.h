#pragma once

#include "Enemy.h"

class Minion : public Enemy
{
public:
	Minion(float x, float y, Game * game);
	Projectile* shootPlayer() override;
};

