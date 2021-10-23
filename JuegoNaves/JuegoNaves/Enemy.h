#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "Projectile.h"

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, float fileWidth, float fileHeight, Game* game);
	void draw() override; // Va a sobrescribir
	virtual void update();
	Animation* aMoving = nullptr;
	Animation* animation = nullptr; // Referencia a la animación mostrada

	int shootCadence = 0;
	int shootTime = -1;
	virtual Projectile* shootPlayer();
};

