#include "engine.hpp"
#include <iostream>

void Engine::Init(const char* Title, const int witdh, const int height)
{
	WindowWidth = witdh;
	WindowHeight = height;

	SDL_CreateWindowAndRenderer(Title, witdh, height, 0, &Window, &Renderer);

	if (!Renderer)
		SDL_Log("Renderer creation failed: %s", SDL_GetError());
	SDL_SetRenderScale(Renderer, 2, 2);

	map.InitializeGrid(20,10);
	RenderSys.Init(Renderer);
}

void Engine::Deinit()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

}

