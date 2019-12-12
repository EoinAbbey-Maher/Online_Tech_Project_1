#include "Game.h"
#include <iostream>
#include <GameClient.h>

using namespace std;

Game* game = nullptr;

int main(int argc, char** argv)
{
	game = new Game();

	game->init("Online Tech Multiplayer Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	game->loadContent();

	while (game->isRunning())
	{
		game->processEvents();
		game->update();
		game->render();

	}

	game->cleanup();
	game->unloadContent();

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Quit();
	
	return 1; // success
}