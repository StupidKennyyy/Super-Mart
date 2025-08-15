#include <SDL3/SDL.h>
#include <engine.hpp>
#include <camera.hpp>
#include <input.h>

class Game {

public:
	
	bool isRunning = false;

	Engine engine;
	Camera camera;
	Map map;
	Input input;

public:

	void Init(const char* title, int width, int height);

	void Run();

	void DeInit();

	void Render();
	
	Game() {}
	~Game() {}

private:

	void UpdateCamera();

};