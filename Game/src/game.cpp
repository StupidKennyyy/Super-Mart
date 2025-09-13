#include "game.hpp"

void Game::Init(const char* title, int width, int height)
{
	engine.Init(title, width, height);

	map.InitializeGrid(20,20, engine.coordinator);

	renderer = engine.Renderer;

	Camera PlayerCam = engine.cameraManager.CreateCamera();
	engine.cameraManager.SetActiveCamera(PlayerCam);

	Camera active = engine.cameraManager.GetActiveCamera();

	engine.cameraManager.SetData(active, CameraData{ .Position = Vector2{100,100} });

	player.CreatePlayer(Transform{
		.Position = {100,100},
		.Size = {40,40}
		},
		engine.coordinator,
		engine.cameraManager
	);

}

void Game::Run()
{

	while (engine.isRunning) {
	
		input.ProcessInput(engine.isRunning);

		engine.inputSys->Update(engine.coordinator, input);

		engine.cameraSys->Update(engine.cameraManager, engine.coordinator);

		engine.movementSys->Update(engine.coordinator);

		engine.collisionSys->Update(engine.coordinator, map);

		engine.Render();

		input.updateState();
	}

}


void Game::DeInit()
{

	engine.Deinit();


}