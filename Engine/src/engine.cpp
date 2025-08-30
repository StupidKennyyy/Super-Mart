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

	coordinator.Init();

	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<Vector2>();
	coordinator.RegisterComponent<RigidBody>();
	coordinator.RegisterComponent<Collider>();
	coordinator.RegisterComponent<Tile>();
	coordinator.RegisterComponent<Sprite>();

	tileRenderSys = coordinator.RegisterSystem<TileRenderSystem>();
	Signature tileRenderSig;
	tileRenderSig.set(coordinator.GetComponentType<Transform>(), true);
	tileRenderSig.set(coordinator.GetComponentType<Tile>(), true);
	coordinator.SetSystemSignature<TileRenderSystem>(tileRenderSig);

	spriteRenderSys = coordinator.RegisterSystem<SpriteRenderSystem>();
	Signature spriteRenderSig;
	spriteRenderSig.set(coordinator.GetComponentType<Transform>(), true);
	spriteRenderSig.set(coordinator.GetComponentType<Sprite>(), true);

	assetManager.LoadTextures(GetAssetsPath(), Renderer);

	tileRenderSys->init(Renderer);
	spriteRenderSys->init(Renderer);

	isRunning = true;

}

void Engine::Deinit()
{
	assetManager.DeloadTextures();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

}

