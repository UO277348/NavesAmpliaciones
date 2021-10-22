#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game) {

	vx = 1; aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, game);
	animation = aMoving;
}


void Enemy::update() {
	/*x = x + vx;
	if (x - width / 2 <= 0 || x + width / 2 >= WIDTH) {
		vx = vx * -1;
	}*/

	if (shootTime > 0) {
		shootTime--;
	}

	// Actualizar la animación
	animation->update();

	vx = -1;
	x = x + vx;
}

void Enemy::draw() {
	animation->draw(x, y);
}

Projectile* Enemy::shootPlayer() {
	if(shootTime == 0) {
		shootTime = shootCadence;
		return new Projectile("res/disparo_enemigo.png",x, y, game, true);
	}
	else {
		return NULL;
	}
}


