#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) {

}

void Player::update() {
	if (shootTime > 0) {
		shootTime--;
	}
	//if (invulnerableTime == 0) {
	//	isInvulnerable = false;
	//}
	invulnerableTime--;
	x = x + vx;
	y = y + vy;
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::shoot() {
	if (shootTime == 0 && munition>0) {
		munition--;
		shootTime = shootCadence;
		return new Projectile(x, y, game);
	}
	else {
		return NULL;
	}

}

bool Player::isOverlap(Actor* actor) {
	bool juntitos = Actor::isOverlap(actor);

	if (juntitos && !isInvulnerable) {
		isInvulnerable = true;
		invulnerableTime = 30;
	}
	else if (juntitos && isInvulnerable)
		juntitos = false;
		
	

	return juntitos;
}
