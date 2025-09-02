#include <SDL3/SDL.h>
#include <engine.hpp>
#include <camera.hpp>
#include <input.hpp>
#include <ecs.hpp>
#include <components.hpp>
#include <SDL3_image/SDL_image.h>
#include <map.hpp>
#include "player.hpp"


class Game {

public:
	
	Player player;

	Engine engine;

	Map map;

	Input input;

	SDL_Renderer* renderer;

public:

	void Init(const char* title, int width, int height);

	void Run();

	void DeInit();

	
	Game() {}
	~Game() {}

};