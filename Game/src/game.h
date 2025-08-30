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
	
	Engine engine;
	Map map;
	Input input;
	CameraManager cameraManager;

	SDL_Renderer* renderer;

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