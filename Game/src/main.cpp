// Super Mart.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <SDL3/SDL.h>
#include "game.h"

int main()
{
	Game game;
	game.Init("Super Mart", 800, 600);
	game.Run();
	game.DeInit();

	
}
