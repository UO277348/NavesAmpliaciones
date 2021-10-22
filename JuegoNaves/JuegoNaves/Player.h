#pragma once

#include "Actor.h"
#include "Projectile.h" 

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	bool isOverlap(Actor* enemy) override;
	int shootCadence = 30;
	int shootTime = 0;
	int invulnerableTime = 0;
	bool isInvulnerable = false;
};
