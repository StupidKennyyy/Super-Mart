#include "game.h"
#include <pathUtils.hpp>

void Game::Init(const char* title, int width, int height)
{
	engine.Init(title, width, height);

	cameraManager.SetPosition({ 0,0 });

	map.InitializeGrid(20,20, engine.coordinator);

	renderer = engine.GetRenderer();

}

void Game::Run()
{

	while (engine.isRunning) {
	
		input.ProcessInput(engine.isRunning);

		UpdateCamera();

		Render();

		input.updateState();
	}

}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
	SDL_RenderClear(renderer);

	engine.tileRenderSys->Render(engine.coordinator, cameraManager.GetPosition());

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