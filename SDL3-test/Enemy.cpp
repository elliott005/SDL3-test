#include "enemy.hpp"

Enemy::Enemy(double x, double y) {
	rect.x = x;
	rect.y = y;
	rect.w = 75.0;
	rect.h = 25;
	shootTimer = shootTimerMax;
	if (rand() % 2 == 0) {
		dir = -1;
	}
	speed += rand() % 50 - 25;
}

Enemy::~Enemy() {

}

bool Enemy::update(double dt, int screenHeight, std::vector<SDL_FRect>* enemyBullets, std::vector<SDL_FRect> playerBullets) {
	rect.y += dir * speed * dt;
	if (rect.y > screenHeight - rect.h) {
		dir *= -1;
		rect.y = screenHeight - rect.h;
	}
	if (rect.y < 0) {
		dir *= -1;
		rect.y = 0;
	}
	shootTimer -= dt;
	if (shootTimer <= 0.0) {
		shootTimer = shootTimerMax;
		enemyBullets->push_back({ rect.x, rect.y + rect.h / 2, 10, 5 });
	}

	for (int i = 0; i < playerBullets.size(); i++) {
		if (SDL_HasRectIntersectionFloat(&rect, &playerBullets[i])) {
			printf("Killed Enemy!!! Bullet id: %i\n", i);
			return true;
		}
	}
	return false;
}

void Enemy::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}