#include "game.h"

void Game::Init(const char* title, int width, int height)
{
	map.InitializeGrid(20,20);
	engine.Init(title, width, height);
	isRunning = true;

}

void Game::Run()
{
	SDL_Event e;

	camera.x = 160 - 400;
	camera.y = 160 - 300;

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

	map.RenderGrid(engine.GetRenderer(), camera);

	SDL_RenderPresent(renderer);


}

void Game::UpdateCamera()
{

	if (input.isKeyDown(SDL_SCANCODE_W))
		camera.y += 0.01f;
	
	if (input.isKeyDown(SDL_SCANCODE_S))
		camera.y -= 0.01f;

	if (input.isKeyDown(SDL_SCANCODE_A))
		camera.x += 0.01f;

	if (input.isKeyDown(SDL_SCANCODE_D))
		camera.x -= 0.01f;

}

void Game::DeInit()
{

	engine.Deinit();


}