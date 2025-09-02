#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <ecs.hpp>
#include <render_systems.hpp>
#include <asset_manager.hpp>
#include <camera.hpp>
#include <movement_system.hpp>
#include <input_system.hpp>

class Engine {

public:

	void Init(const char* Title, const int witdh, const int height);

	void Deinit();

	Engine() {};

	void Render(CameraManager& cameraManager);

public:

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	
	Coordinator coordinator;

	std::shared_ptr<TileRenderSystem> tileRenderSys;
	std::shared_ptr<SpriteRenderSystem> spriteRenderSys;
	std::shared_ptr<InputSystem> inputSys;
	std::shared_ptr<MovementSystem> movementSys;

	AssetManager assetManager;
	
	int WindowHeight = 0;
	int WindowWidth = 0;
	
	bool isRunning = false;
};
