#include "player.hpp"

Player::Player(SDL_Renderer* renderer, double x, double y) {
	if (x != NULL) {
		posX = x;
	}
	if (y != NULL) {
		posY = y;
	}
	sprite.loadFromFile(spriteName, renderer);
	
	rect.w = 170.0;
	rect.h = 50.0;
	updateRectPos();
}

Player::~Player() {
	sprite.destroy();
}

void Player::update(double dt, bool inputJump, bool inputShoot, int screenWidth, int screenHeight, std::vector<Wall> walls, std::vector<SDL_FRect>* enemyBullets, int* score) {
	velocityY += dt * gravityAccel;
	velocityY = std::min(velocityY, gravityMax);
	if (inputJump) {
		velocityY = jumpStr;
	}
	posY += velocityY * dt;

	posY = std::min(std::max(posY, 0.0), double(screenHeight - rect.h - 25.0));

	updateRectPos();

	for (int i = 0; i < walls.size(); i++) {
		for (SDL_FRect other_rect : walls[i].rects) {
			bool coll = SDL_HasRectIntersectionFloat(&rect, &other_rect);
			if (coll) {
				printf("Hit Wall!!! Wall id: %i\n", i);
				*score = 0;
			}
		}
	}

	for (int i = enemyBullets->size() - 1; i >= 0; i--) {
		if (SDL_HasRectIntersectionFloat(&rect, &(*enemyBullets)[i])) {
			printf("Hit Bullet!!! Bullet id: %i\n", i);
			*score = std::max(0, *score - 5);
			enemyBullets->erase(std::next(enemyBullets->begin(), i));
		}
	}

	if (inputShoot) {
		bullets.push_back(SDL_FRect{ float(posX) + rect.w, float(posY), 20, 10 });
	}

	updateBullets(dt, screenWidth);
}

void Player::updateRectPos() {
	rect.x = posX + 10.0;
	rect.y = posY + 25.0;
}

void Player::updateBullets(double dt, int screenWidth) {
	for (SDL_FRect& rect : bullets) {
		rect.x += bulletSpeed * dt;
	}
	/*for (std::vector<SDL_FRect>::iterator it = bullets.end(); it != bullets.begin(); it--) {
		if (it->x > screenWidth) {
			it = bullets.erase(it);
		}
	}*/
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [screenWidth](SDL_FRect rect) {return rect.x > screenWidth; }), bullets.end());
	//printf("size: %i\n", bullets.size());
}

void Player::draw(SDL_Renderer* renderer) {
	sprite.render(posX, posY, renderer);
	drawBullets(renderer);
}

void Player::drawBullets(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (SDL_FRect rect : bullets) {
		SDL_RenderFillRect(renderer, &rect);
	}
}