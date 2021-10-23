#include "Minion.h"

Minion::Minion(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 36, 40, game) {

	vx = -1;
	shootCadence = 50;
	shootTime = 5;
	vidas = 1;

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, game);
	animation = aMoving;
}

Projectile* Minion::shootPlayer() {
	if (shootTime == 0) {
		shootTime = shootCadence;
		return new Projectile("res/disparo_enemigo.png", x, y, game, true);
	}
	else {
		return NULL;
	}
}