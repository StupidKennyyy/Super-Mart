#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <ecs/ecs.hpp>
#include <assets/asset_manager.hpp>
#include <camera/camera.hpp>
#include <utils/path_utils.hpp>

class Engine {

public:

	void Init(const char* Title, const int witdh, const int height);

	void Deinit();

	Engine() {};

	void Render();

public:

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	
	Coordinator coordinator;

	AssetManager assetManager;

	CameraManager cameraManager;

	int WindowHeight = 0;
	int WindowWidth = 0;
	
	bool isRunning = false;
};
