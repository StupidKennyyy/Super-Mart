#include <input/input.hpp>

//
// Keyboard
//

// Key set

void Input::onKeyDown(SDL_Scancode sc)
{
	auto& state = keyInputStates[sc];
	state.isDown = true;
}

void Input::onKeyUp(SDL_Scancode sc)
{
	auto& state = keyInputStates[sc];
	state.isDown = false;
}

// Key get

bool Input::wasKeyPressed(SDL_Scancode sc)
{
	auto it = keyInputStates.find(sc);
	if (it != keyInputStates.end())
	{
		return it->second.isDown && !it->second.wasDownLastFrame;
	}

	return false;
}

bool Input::isKeyDown(SDL_Scancode sc)
{
	auto it = keyInputStates.find(sc);
	if (it != keyInputStates.end())
	{
		return it->second.isDown;
	}
	return false;
}

bool Input::wasKeyReleased(SDL_Scancode sc)
{
	auto it = keyInputStates.find(sc);
	if (it != keyInputStates.end())
	{
		return !it->second.isDown && it->second.wasDownLastFrame;
	}

	return false;
}


//
// Mouse
//

// Mouse set

void Input::onButtonDown(Uint8 button)
{
	auto& state = mouseInputStates[button];
	state.isDown = true;
	
} 
void Input::onButtonUp(Uint8 button)
{
	auto& state = mouseInputStates[button];
	state.isDown = false;
}

// Mouse get

bool Input::wasMouseButtonPressed(Uint8 button)
{ 
	auto it = mouseInputStates.find(button);

	if (it != mouseInputStates.end())
	{
		return it->second.isDown && !it->second.wasDownLastFrame;
	}
	return false;

}

bool Input::isMouseButtonDown(Uint8 button)
{
	auto it = mouseInputStates.find(button);
	if (it != mouseInputStates.end())
	{
		return it->second.isDown;
	}
	return false;
}

bool Input::wasMouseButtonReleased(Uint8 button)
{
	auto it = mouseInputStates.find(button);
	if (it != mouseInputStates.end())
	{
		return !it->second.isDown && it->second.wasDownLastFrame;
	}
	return false;
}

Vector2 Input::getMousePosition()
{	
	Vector2 mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	return mousePos;
}

// Handle input

void Input::ProcessInput(bool& isRunning)
{
	SDL_Event e;
	
	while (SDL_PollEvent(&e))
	{
		switch (e.type) {
			
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;

			case SDL_EVENT_KEY_DOWN:
				onKeyDown(e.key.scancode);
				break;

			case SDL_EVENT_KEY_UP:
				onKeyUp(e.key.scancode);
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				onButtonDown(e.button.button);
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP:
				onButtonUp(e.button.button);
				break;
		}
	}
}

void Input::updateState()
{
	
	for (auto& button : mouseInputStates)
		button.second.wasDownLastFrame = button.second.isDown;

	for (auto& key : keyInputStates)
		key.second.wasDownLastFrame = key.second.isDown;

}
