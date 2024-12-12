#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>

class Enemy {
public:
	Enemy(double x, double y);
	~Enemy();

	bool update(double dt, int screenHeight, std::vector<SDL_FRect>* enemyBullets, std::vector<SDL_FRect> playerBullets);
	void draw(SDL_Renderer* renderer);
private:
	SDL_FRect rect;
	double speed = 100.0;
	int dir = 1;
	double shootTimerMax = 3.0;
	double shootTimer;
};