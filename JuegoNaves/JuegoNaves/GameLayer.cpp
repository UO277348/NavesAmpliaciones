#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.07, game);
	textPoints->content = to_string(points);

	vidas = 3;
	textVida = new Text("vidas", WIDTH * 0.72, HEIGHT * 0.07, game);
	textVida->content = to_string(vidas);

	player = new Player(50, 50, game);

	textMunicion = new Text("municion", WIDTH * 0.52, HEIGHT * 0.07, game);
	textMunicion->content = to_string(player->munition);

	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1,game);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.07, 24, 24, game);
	backgroundVidas = new Actor("res/corazon.png",
		WIDTH * 0.65, HEIGHT * 0.07, 44, 36, game);
	backgroundDisparos = new Actor("res/disparo_jugador.png",
		WIDTH * 0.45, HEIGHT * 0.07, 18, 6, game);

	projectiles.clear(); // Vaciar por si reiniciamos el juego

	enemies.clear(); // Vaciar por si reiniciamos el juego
	enemies.push_back(new Minion(300, 50, game));
	enemies.push_back(new Minion(300, 200, game));

	recolectables.clear();
	recolectables.push_back(new CajaMunicion(300, 125, game));
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}

	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}
	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
		return;
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		case SDLK_1:
			game->scale();
			break;
		}

	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1){
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
	}

	}
}

void GameLayer::update() {
	textMunicion->content = to_string(player->munition);
	background->update();
	// Generar enemigos
	newEnemyTime--;
	newBossTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;

		if (newBossTime<=0) {
			enemies.push_back(new Boss(rX, rY, game));
			newBossTime = 300;
		}
		else
			enemies.push_back(new Minion(rX, rY, game));

		newEnemyTime = 110;
	}

	newRecolectbale--;
	if (newRecolectbale <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		recolectables.push_back(new CajaMunicion(rX,rY,game));
		newRecolectbale = 200;
	}


	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		Projectile* newProjectile = enemy->shootPlayer();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& caja : recolectables) {
		caja->update();
	}

	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			if (vidas > 1) {
				vidas--;
				textVida->content = to_string(vidas);
			}
			else {
				init();
			}
			
			return; // Cortar el for
		}
	}

	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<CajaMunicion*> deleteCajas;

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile) && !projectile->enemyShot && enemy->vidas==1) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);

					//Aqui no habría problema
					player->munition++;
					points++;
					textPoints->content = to_string(points);
					textMunicion->content = to_string(player->munition);
				}
				//Cuidado que si colisionan 2 cuenta dos aunque elimines 1
				/*points++;
				textPoints->content = to_string(points);*/

			}
			else if(enemy->isOverlap(projectile) && !projectile->enemyShot && enemy->vidas > 1){
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->vidas--;
			}

			if (player->isOverlap(projectile) && projectile->enemyShot) {
				if (vidas > 1) {
					vidas--;
					textVida->content = to_string(vidas);
				}
				else {
					init();
				}
				return;
			}
		}
	}

	for (auto const& caja : recolectables) {
		if (player->isOverlap(caja)) {
			bool cajaInList = std::find(deleteCajas.begin(),
				deleteCajas.end(),
				caja) != deleteCajas.end();

			if (!cajaInList) {
				deleteCajas.push_back(caja);

				player->munition += caja->munExtra;
				textMunicion->content = to_string(player->munition);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
	}
	deleteProjectiles.clear();

	for (auto const& delCaja : deleteCajas) {
		recolectables.remove(delCaja);
	}
	deleteCajas.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();

	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	player->draw();

	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	for (auto const& caja : recolectables) {
		caja->draw();
	}

	textPoints->draw();
	textVida->draw();
	textMunicion->draw();
	backgroundPoints->draw();
	backgroundVidas->draw();
	backgroundDisparos->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}
