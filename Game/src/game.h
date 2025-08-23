#include <SDL3/SDL.h>
#include <engine.hpp>
#include <camera.hpp>
#include <input.hpp>
#include <ecs.hpp>
#include <components.hpp>
#include <renderSystems.hpp>
#include <asset_manager.hpp>
#include <SDL3_image/SDL_image.h>
#include <map.hpp>

class Game {

public:
	
	bool isRunning = false;

	Engine engine;
	Map map;
	Input input;
	Coordinator coordinator;
	CameraManager cameraManager;

	std::shared_ptr<TileRenderSystem> tileRenderSys;
	std::shared_ptr<SpriteRenderSystem> spriteRenderSys;

	AssetManager assetManager;

public:

	void Init(const char* title, int width, int height);

	void Run();

	void DeInit();

	void Render();
	
	Game() : cameraManager(input) {}
	~Game() {}

private:

	void UpdateCamera();

};