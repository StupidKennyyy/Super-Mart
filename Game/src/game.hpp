#include "player.hpp"
#include <include.hpp>


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

};