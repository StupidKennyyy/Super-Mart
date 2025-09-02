#include "game.hpp"
#include <pathUtils.hpp>

void Game::Init(const char* title, int width, int height)
{
	engine.Init(title, width, height);

	cameraManager.SetPosition({ 0,0 });

	map.InitializeGrid(20,20, engine.coordinator);

	renderer = engine.Renderer;

	player.CreatePlayer(Transform{
		.Position = {100,100},
		.Size = {20,20}
		}, 
		engine.coordinator
	);

}

void Game::Run()
{

	while (engine.isRunning) {
	
		input.ProcessInput(engine.isRunning);

		cameraManager.Update();

		engine.inputSys->Update(engine.coordinator, input);

		engine.movementSys->Update(engine.coordinator);

		engine.Render(cameraManager);

		input.updateState();
	}

}


void Game::DeInit()
{

	engine.Deinit();


}