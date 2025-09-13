#include <iostream>
#include "game.hpp"
#include <include.hpp>

int main()
{
	Game game;
	game.Init("Super Mart", 800, 600);
	game.Run();
	game.DeInit();

	
}
