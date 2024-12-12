#include "wall.hpp"

//LPC spritesheet generator

Wall::Wall(SDL_Renderer* renderer, double x, double y) {
	posX = x;
	posY = y;
	for (SDL_FRect& rect : rects) {
		rect.w = 50.0;
		rect.h = 300.0 + double(randomRange);
	}
}

Wall::~Wall() {

}

void Wall::update(double dt) {
	posX -= dt * speed;
	int i = 0;
	for (SDL_FRect& rect : rects) {
		rect.x = posX;
		rect.y = posY + (distBetweenWalls + rect.h) * i + heightOffset;
		i++;
	}
}

void Wall::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for (SDL_FRect rect : rects) {
		SDL_RenderFillRect(renderer, &rect);
	}
}

bool Wall::inBounds(double min) {
	return (posX > min);
}

void Wall::setX(double val) {
	posX = val;
}

void Wall::randomY() {
	posY = rand() % (randomRange + 1) - randomRange / 2;
}