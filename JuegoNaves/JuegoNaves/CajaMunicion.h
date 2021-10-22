#pragma once

#include "Actor.h"
#include "Animation.h" 

class CajaMunicion : public Actor
{
public:
	CajaMunicion(float x, float y, Game* game);

	void draw() override; // Va a sobrescribir
	void update();

	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada

	int munExtra;
};

