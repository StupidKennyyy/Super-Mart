#include "engine.hpp"
#include <iostream>

void Engine::Init(const char* Title, const int witdh, const int height)
{
	SDL_Init(SDL_INIT_VIDEO);

	WindowWidth = witdh;
	WindowHeight = height;

	SDL_CreateWindowAndRenderer(Title, witdh, height, 0, &Window, &Renderer);

	if (!Renderer)
		SDL_Log("Renderer creation failed: %s", SDL_GetError());
	SDL_SetRenderScale(Renderer, 2, 2);

}

void Engine::Deinit()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

}

