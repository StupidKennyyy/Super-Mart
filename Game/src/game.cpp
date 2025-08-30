#include "game.h"
#include <pathUtils.hpp>

void Game::Init(const char* title, int width, int height)
{
	engine.Init(title, width, height);
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

	assetManager.LoadTextures(GetAssetsPath(), engine.GetRenderer());

	cameraManager.SetPosition({ 0,0 });

	map.InitializeGrid(20,20, coordinator);

	tileRenderSys->init(engine.GetRenderer());
	spriteRenderSys->init(engine.GetRenderer());

}

void Game::Run()
{
	SDL_Event e;


	while (engine.isRunning) {
	
		input.ProcessInput(engine.isRunning);

		UpdateCamera();

		Render();

		input.updateState();
	}

}

void Game::Render()
{
	SDL_Renderer* renderer = engine.GetRenderer();

	SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
	SDL_RenderClear(renderer);

	tileRenderSys->Render(coordinator, cameraManager.GetPosition());

	SDL_RenderPresent(renderer);


}

void Game::UpdateCamera()
{
	cameraManager.Update();
}

void Game::DeInit()
{

	engine.Deinit();


}