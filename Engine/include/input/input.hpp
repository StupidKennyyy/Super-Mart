#pragma once

#include <unordered_map>
#include <SDL3/SDL.h>
#include <components/components.hpp>

class Input {

private:

	struct State
	{
		bool isDown = false;
		bool wasDownLastFrame = false;
	};
		
	std::unordered_map<SDL_Scancode, State> keyInputStates;
	std::unordered_map<Uint8, State> mouseInputStates;


private:

	void onKeyDown(SDL_Scancode sc);
	void onKeyUp(SDL_Scancode sc);
	
	void onButtonDown(Uint8 button);
	void onButtonUp(Uint8 button);	
	


public:

	bool wasKeyPressed(SDL_Scancode sc);
	bool isKeyDown(SDL_Scancode sc);
	bool wasKeyReleased(SDL_Scancode sc);

	bool wasMouseButtonPressed(Uint8 button);
	bool isMouseButtonDown(Uint8 button);
	bool wasMouseButtonReleased(Uint8 button);

	Vector2 getMousePosition();
	void ProcessInput(bool& isRunning);

	void updateState();
};