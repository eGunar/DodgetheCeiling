#include "game.h"
#include "texturemanager.h"
#include "GameObject.h"
#include "map.h"
#include "ECS.h"
#include "components.h"

GameObject* player;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Initialized\n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created\n";
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created\n";
		}
		isRunning = true;
	}
	player = new GameObject("assets/PlayerDown.png", 0, 0);
	map = new Map();

	newPlayer.addComponent<PositionComponent>();
	newPlayer.addComponent<PositionComponent>().setPos(500, 500);

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	player->Update();
	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," <<
		newPlayer.getComponent<PositionComponent>().x() << std::endl;

}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game quit..\n";
}
