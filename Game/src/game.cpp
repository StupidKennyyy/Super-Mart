#include "game.h"

void Game::Init(const char* title, int width, int height)
{
	map.InitializeGrid(20,20);
	engine.Init(title, width, height);
	coordinator.Init();
	isRunning = true;

	cameraManager.SetPosition({ 0,0 });

}

void Game::Run()
{
	SDL_Event e;


	while (true) {
	
		input.ProcessInput(e);

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

	map.RenderGrid(engine.GetRenderer(), cameraManager.GetPosition());

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