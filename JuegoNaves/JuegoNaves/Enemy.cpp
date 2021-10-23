#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, float fileWidth, float fileHeight, Game* game)
	: Actor(filename, x, y, fileWidth, fileHeight, game) {

	vx = 1;
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


