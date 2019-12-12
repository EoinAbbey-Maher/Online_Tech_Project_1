#ifndef GAME_HPP
#define GAME_HPP
	
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>

#include "GameClient.h"
#include "Dot.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* t_title, int t_xpos, int t_ypos, int t_width, int t_height, bool t_isFullScreen);
	void loadContent();
	void unloadContent();

	void processEvents();

	bool isRunning();

	void update();

	void render();
	void cleanup();

	
private:
	GameClient * m_serverClient = new GameClient("149.153.106.156", 1111);
	bool m_isRunning{ false };

	Dot* m_player_One_Dot;
	Dot* m_player_Two_Dot;

	int m_windowHeight;
	int m_windowWidth;

	SDL_Window * m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Surface* m_surface;

	SDL_Rect m_source;
	SDL_Rect m_destination;
};

#endif // !GAME_HPP

