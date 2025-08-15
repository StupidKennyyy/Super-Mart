#pragma once

#include <SDL3/SDL.h>
#include <vector>

class RenderSystem {

private:

	SDL_Renderer* Renderer = nullptr;	


public:

	RenderSystem() { }

	~RenderSystem()
	{
		SDL_DestroyRenderer(Renderer);
	}

	void Init(SDL_Renderer* R)
	{
		Renderer = R;
	}


};
