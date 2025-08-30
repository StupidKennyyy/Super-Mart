#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Engine {

public:

	void Init(const char* Title, const int witdh, const int height);

	void Deinit();

	Engine() {};

	SDL_Renderer* GetRenderer() const
	{
		return Renderer;
	}

	SDL_Window* GetWindow() const
	{
		return Window;
	}

public:

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	
	int WindowHeight = 0;
	int WindowWidth = 0;
	
	bool isRunning = false;
};
