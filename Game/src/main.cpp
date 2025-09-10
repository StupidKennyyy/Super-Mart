#include <iostream>
#include <SDL3/SDL.h>
#include "game.hpp"

int main()
{
	Game game;
	game.Init("Super Mart", 800, 600);
	game.Run();
	game.DeInit();

	
}
