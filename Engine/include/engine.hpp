#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <ecs.hpp>
#include <renderSystems.hpp>
#include <asset_manager.hpp>

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
	
	Coordinator coordinator;

	std::shared_ptr<TileRenderSystem> tileRenderSys;
	std::shared_ptr<SpriteRenderSystem> spriteRenderSys;

	AssetManager assetManager;

	int WindowHeight = 0;
	int WindowWidth = 0;
	
	bool isRunning = false;
};
