#include <core/game.hpp>

void Game::Init(const char* title, int width, int height)
{
	engine.Init(title, width, height);

	InitializeGameSystems(engine.coordinator);

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

		//
		// Update
		//

		inputSys->Update(engine.coordinator, input);

		cameraSys->Update(engine.cameraManager, engine.coordinator);

		movementSys->Update(engine.coordinator, deltaTime);

		collisionSys->Update(engine.coordinator, map);

		//
		// Render
		//

		SDL_SetRenderDrawColor(engine.Renderer,0, 0, 0, 255);
		SDL_RenderClear(engine.Renderer);

		spriteRenderSys->Render(engine.coordinator, engine.cameraManager.GetActiveCameraData().Position);

		SDL_RenderPresent(engine.Renderer);

	

		input.updateState();
		UpdateDeltaTime();
	}

}

void Game::UpdateDeltaTime()
{
	now = SDL_GetTicks();
	deltaTime = (now - last) / 1000.0f;
	last = now;
}

void Game::InitializeGameSystems(Coordinator& coordinator)
{
	//
	// Components
	//

	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<Vector2>();
	coordinator.RegisterComponent<RigidBody>();
	coordinator.RegisterComponent<Collider>();
	coordinator.RegisterComponent<Tile>();
	coordinator.RegisterComponent<Sprite>();
	coordinator.RegisterComponent<InputComponent>();
	coordinator.RegisterComponent<CameraFollow>();

	//
	// Systems
	//

	tileRenderSys = coordinator.RegisterSystem<TileRenderSystem>();
	Signature tileRenderSig;
	tileRenderSig.set(coordinator.GetComponentType<Transform>(), true);
	tileRenderSig.set(coordinator.GetComponentType<Tile>(), true);
	coordinator.SetSystemSignature<TileRenderSystem>(tileRenderSig);


	spriteRenderSys = coordinator.RegisterSystem<SpriteRenderSystem>();
	Signature spriteRenderSig;
	spriteRenderSig.set(coordinator.GetComponentType<Transform>(), true);
	spriteRenderSig.set(coordinator.GetComponentType<Sprite>(), true);
	coordinator.SetSystemSignature<SpriteRenderSystem>(spriteRenderSig);


	movementSys = coordinator.RegisterSystem<MovementSystem>();
	Signature movSig;
	movSig.set(coordinator.GetComponentType<InputComponent>(), true);
	movSig.set(coordinator.GetComponentType<Transform>(), true);
	movSig.set(coordinator.GetComponentType<RigidBody>(), true);
	coordinator.SetSystemSignature<MovementSystem>(movSig);


	inputSys = coordinator.RegisterSystem<InputSystem>();
	Signature inputSig;
	inputSig.set(coordinator.GetComponentType<InputComponent>(), true);
	coordinator.SetSystemSignature<InputSystem>(inputSig);


	cameraSys = coordinator.RegisterSystem<CameraSystem>();
	Signature camSig;
	camSig.set(coordinator.GetComponentType<CameraFollow>(), true);
	camSig.set(coordinator.GetComponentType<Transform>(), true);
	camSig.set(coordinator.GetComponentType<RigidBody>(), true);
	coordinator.SetSystemSignature<CameraSystem>(camSig);

	collisionSys = coordinator.RegisterSystem<CollisionSystem>();
	Signature colSig;
	colSig.set(coordinator.GetComponentType<Collider>(), true);
	coordinator.SetSystemSignature<CollisionSystem>(colSig);

	spriteRenderSys->init(engine.Renderer);
}


void Game::DeInit()
{

	engine.Deinit();


}