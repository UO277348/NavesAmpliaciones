#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	virtual void draw();
	virtual bool isOverlap(Actor* actor);
	bool isInRender();
	SDL_Texture* texture;
	float x;
	float y;
	float vx;
	float vy;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game; // referencia al juego
};


