#include "CajaMunicion.h"

CajaMunicion::CajaMunicion(float x, float y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 40, game)
{
	vx = 1;
	aMoving = new Animation("res/recolectable.png", width, height,
		256, 32, 3, 8, game);
	animation = aMoving;

	munExtra = rand()%10+1;
}



void CajaMunicion::update() {
	animation->update();

	vx = -1;
	x = x + vx;
}

void CajaMunicion::draw() {
	//Actor::draw(); // llamar al metodo del hijo

	animation->draw(x, y);

}