#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* t_title, int t_xpos, int t_ypos, int t_width, int t_height, bool t_isFullScreen)
{
	int flags = 0;
	if (t_isFullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Initialised " << std::endl;

		m_window = SDL_CreateWindow(t_title, t_xpos, t_ypos, t_width, t_height, flags);

		m_windowHeight = t_height;
		m_windowWidth = t_width;

		if (m_window)
		{
			std::cout << "window created" << std::endl;
		}
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer)
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

			m_isRunning = true;
		}
		else
		{
			m_isRunning = false;
		}
	}

	m_player_One_Dot = new Dot(true, m_serverClient);
	m_player_Two_Dot = new Dot(false, m_serverClient);

	
	m_player_One_Dot->SetPosition(50, 50);
	m_player_Two_Dot->SetPosition(500, 500);

	m_player_One_Dot->move(m_windowHeight, m_windowWidth);
	m_player_Two_Dot->move(m_windowHeight, m_windowWidth);



	if (!m_serverClient->Connect())
	{
		std::cout << "Failed to connect to server..." << std::endl;
	}

	loadContent();
	
}

void Game::loadContent()
{
	m_player_One_Dot->Init(m_renderer, "Resources/BlueDot.bmp");
	m_player_Two_Dot->Init(m_renderer, "Resources/RedDot.bmp");
}

void Game::unloadContent()
{
}

void Game::processEvents()
{
	SDL_Event event;

		SDL_PollEvent(&event);

		m_player_One_Dot->handleEvent(event);
		m_player_Two_Dot->handleEvent(event);
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;
		default:
			break;
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				std::cout << "Space Pressed" << std::endl;
				m_serverClient->SendString("Space Key Pressed");
				break;
			default:
				break;
			}

	}

}

bool Game::isRunning()
{
	return m_isRunning;
}

void Game::update()
{
	m_player_One_Dot->move(m_windowHeight, m_windowWidth);
	m_player_Two_Dot->move(m_windowHeight, m_windowWidth);
	m_serverClient->m_recievedMessage = "";
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	if (m_renderer != nullptr && m_texture != nullptr)
	{
		SDL_Rect* testRect = new SDL_Rect();
		testRect->x = 0;
		testRect->y = 0;
		testRect->h = 32;
		testRect->w = 32;
		SDL_RenderCopy(m_renderer, m_texture, testRect , NULL);
	}

	m_player_One_Dot->render(m_renderer);
	m_player_Two_Dot->render(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Game::cleanup()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
