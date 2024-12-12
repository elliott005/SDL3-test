#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

class Wall {
public:
	Wall(SDL_Renderer* renderer, double x, double y);
	~Wall();

	void update(double dt);
	void draw(SDL_Renderer* renderer);
	bool inBounds(double min);
	void setX(double val);
	void randomY();
	SDL_FRect rects[2];

private:
	double posX = 100.0;
	double posY = 100.0;
	double distBetweenWalls = 275.0;
	int speed = 150;
	int randomRange = 150;
	int heightOffset = -100;
};