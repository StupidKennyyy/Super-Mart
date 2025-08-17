#include <SDL3/SDL.h>
#include <engine.hpp>
#include <camera.hpp>
#include <input.h>
#include <ecs.hpp>
#include <components.hpp>

class Game {

public:
	
	bool isRunning = false;

	Engine engine;
	Map map;
	Input input;
	Coordinator coordinator;
	CameraManager cameraManager;

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