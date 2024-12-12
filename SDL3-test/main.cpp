//Using SDL, SDL_image, standard IO, and strings
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
//#include <MySDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


#include "application.hpp"
#include "player.hpp"
#include "Wall.hpp"
#include "Enemy.hpp"



int main( int argc, char* args[] )
{
	srand(time(0));

	Application game;
	Player player(game.m_renderer);
	std::vector<Enemy> enemies;
	std::vector<SDL_FRect> enemyBullets;
	float enemyBulletSpeed = 200.0;
	int extraEnemiesOnKill = 2;
	int scorePerKill = 3;
	int maxEnemies = 7;
	enemies.push_back(Enemy(game.SCREEN_WIDTH - 100, rand() % game.SCREEN_HEIGHT - 200));
	std::vector<Wall> walls;
	int distBetweenWalls = 400;
	for (int i = 0; i <= game.SCREEN_WIDTH / distBetweenWalls + 1; i++) {
		walls.push_back(Wall(game.m_renderer, distBetweenWalls * i, 0.0));
		walls[i].randomY();
	}
	
	double wallStartX = game.SCREEN_WIDTH + distBetweenWalls;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	bool inputJump = false;
	bool inputShoot = false;

	int score = 0;

	//Main loop flag
	bool quit = false;

	double frameRate = 1.0 / 60.0;

	//While application is running
	while( !quit )
	{
		inputJump = false;
		inputShoot = false;

		//Handle events on queue
		while( SDL_PollEvent( &game.m_window_event ) != 0 )
		{
			//User requests quit
			if(game.m_window_event.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}

			if (game.m_window_event.type == SDL_EVENT_KEY_DOWN) {
				switch (game.m_window_event.key.key)
				{
				case SDLK_ESCAPE:
					return 0;
				case SDLK_SPACE:
					inputJump = true;
					inputShoot = true;
					break;
				default:
					break;
				}
			}
		}

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		deltaTime *= 0.001;
		/*if (deltaTime > 0.0) {
			printf("FPS: %f\n", 1.0 / deltaTime);
		}*/

		player.update(deltaTime, inputJump, inputShoot, game.SCREEN_WIDTH, game.SCREEN_HEIGHT, walls, &enemyBullets, &score);

		for (int i = 0; i < walls.size(); i++) {
			walls[i].update(deltaTime);
			if (!walls[i].inBounds(-distBetweenWalls)) {
				walls[i].setX(wallStartX);
				walls[i].randomY();
				score++;
				printf("score: %i\n", score);
			}
		}
		for (int i = enemies.size() - 1; i >= 0; i--) {
			bool destroyed = enemies[i].update(deltaTime, game.SCREEN_HEIGHT, &enemyBullets, player.bullets);
			if (destroyed) {
				enemies.erase(std::next(enemies.begin(), i));
				score += scorePerKill;
				printf("score: %i\n", score);
				for (int _ = 0; _ < extraEnemiesOnKill; _++) {
					if (enemies.size() >= maxEnemies) {
						break;
					}
					enemies.push_back(Enemy(game.SCREEN_WIDTH - 100, rand() % game.SCREEN_HEIGHT - 200));
				}
			}
		}

		for (int i = enemyBullets.size() - 1; i >= 0; i--) {
			enemyBullets[i].x -= enemyBulletSpeed * deltaTime;
			if (enemyBullets[i].x < 0.0) {
				enemyBullets.erase(std::next(enemyBullets.begin(), i));
			}
		}

		player.draw(game.m_renderer);
		for (int i = 0; i < walls.size(); i++) {
			walls[i].draw(game.m_renderer);
		}
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].draw(game.m_renderer);
		}
		SDL_SetRenderDrawColor(game.m_renderer, 0, 0, 255, 255);
		for (int i = 0; i < enemyBullets.size(); i++) {
			SDL_RenderFillRect(game.m_renderer, &enemyBullets[i]);
		}

		game.updateScreen();

		SDL_Delay(std::max(0.0, frameRate - deltaTime) * 1000);
	}

	return 0;
}
