#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include "wall.hpp"
#include "helpers.hpp"

class Player {
public:
	Player(SDL_Renderer* renderer, double x = NULL, double y = NULL);
	~Player();
	void update(double dt, bool inputJump, bool inputShoot, int screenHeight, int screenWidth, std::vector<Wall> walls, std::vector<SDL_FRect>* enemyBullets, int* score);
	void draw(SDL_Renderer* renderer);
	std::vector<SDL_FRect> bullets;
private:
	void updateRectPos();
	void drawBullets(SDL_Renderer* renderer);
	void updateBullets(double dt, int screenWidth);
	double posX = 100.0;
	double posY = 300.0;
	SDL_FRect rect;
	double velocityY = 0.0;
	double bulletSpeed = 300.0;
	double gravityMax = 300.0;
	double gravityAccel = 200.0;
	double jumpStr = -150.0;
	LTexture sprite;
	const char* spriteName = "assets/tom_standing.png";
};