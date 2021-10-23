#include "Boss.h"

Boss::Boss(float x, float y, Game* game)
	: Enemy("res/boss.png", x, y, 40, 40, game) {

	vx = -1;

	shootCadence = 25;
	shootTime = 0;
	tpTime = 0;
	vidas = 3;

	aMoving = new Animation("res/animacion_boss.png", width, height,
		160, 40, 8, 4, game);
	animation = aMoving;
}

Projectile* Boss::shootPlayer() {
	if (shootTime == 0) {
		shootTime = shootCadence;
		return new Projectile("res/disparo_boss.png", x, y, game, true);
	}
	else {
		return NULL;
	}
}

void Boss::tp() {
	if (tpTime == 0) {
		tpTime = shootTime+2;
		int rX;
		do {
			rX = rand() % WIDTH;
		} while (rX < (WIDTH * 50) / 100);

		int rY = rand() % HEIGHT;

		x = rX;
		y = rY;
	}
}

void Boss::update() {
	/*x = x + vx;
	if (x - width / 2 <= 0 || x + width / 2 >= WIDTH) {
		vx = vx * -1;
	}*/

	if (shootTime > 0) {
		shootTime--;
	}

	if (tpTime > 0) {
		tpTime--;
	}
	else
		tp();
		
	// Actualizar la animación
	animation->update();

}