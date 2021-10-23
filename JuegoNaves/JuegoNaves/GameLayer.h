#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "CajaMunicion.h"
#include "Minion.h"
#include "Boss.h"

#include <list>
class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);

	Text* textPoints;
	int points;
	int newEnemyTime = 0;
	int newRecolectbale = 0;

	Text* textVida;
	int vidas = 3;

	Text* textMunicion;

	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundVidas;
	Actor* backgroundDisparos;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<CajaMunicion*> recolectables;
};


