#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador.png", x, y, 18, 6, game) {
	vx = 9;
}

Projectile::Projectile(string filename, float x, float y, Game* game, bool enemyShot) :
	Actor(filename, x, y, 18, 6, game) {
	vx = 9;
	this->enemyShot = enemyShot;
}

void Projectile::update() {
	x = x + vx;
} 
