#pragma once

#include <SDL3/SDL.h>
#pragma once
#include <map.hpp>
#include <camera.hpp>

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
	Map map;
	RenderSystem RenderSys;
	Camera camera;
	
	int WindowHeight = 0;
	int WindowWidth = 0;

};
