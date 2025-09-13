#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <ecs/ecs.hpp>
#include <systems/camera_system.hpp>
#include <systems/collision_system.hpp>
#include <systems/input_system.hpp>
#include <systems/movement_system.hpp>
#include <systems/render_systems.hpp>

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

	std::shared_ptr<TileRenderSystem> tileRenderSys;
	std::shared_ptr<SpriteRenderSystem> spriteRenderSys;
	std::shared_ptr<InputSystem> inputSys;
	std::shared_ptr<MovementSystem> movementSys;
	std::shared_ptr<CameraSystem> cameraSys;
	std::shared_ptr<CollisionSystem> collisionSys;

	AssetManager assetManager;

	CameraManager cameraManager;

	int WindowHeight = 0;
	int WindowWidth = 0;
	
	bool isRunning = false;
};
