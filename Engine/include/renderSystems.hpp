#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <ecs.hpp>
#include <Tile.hpp>
#include <iostream>

class TileRenderSystem : public System {

private:

	SDL_Renderer* Renderer = nullptr;	


public:


	void init(SDL_Renderer* renderer)
	{
		
		Renderer = renderer;

	}

	void Render(Coordinator& coordinator, const Vector2 CameraPosition)
	{

		for (auto entity : this->m_Entites)
		{
			auto& tile = coordinator.GetComponent<Tile>(entity);
			auto& transform = coordinator.GetComponent<Transform>(entity);

			auto& sprite = coordinator.GetComponent<Sprite>(entity);

			float drawX = transform.Position.x + CameraPosition.x;
			float drawY = transform.Position.y + CameraPosition.y;

			SDL_FRect rect = { drawX, drawY, transform.Size.x, transform.Size.y };

			switch (tile.type)
			{
			case TileType::Air:
				SDL_RenderTexture(Renderer, sprite.texture, NULL, &rect);
				break;
			case TileType::Ground:
				SDL_RenderTexture(Renderer, sprite.texture, NULL, &rect);
				break;
			}
			
		}

	}


};

class SpriteRenderSystem : public System {

private:

	SDL_Renderer* Renderer;

public:

	void init(SDL_Renderer* renderer)
	{
		Renderer = renderer;
	}

	void Render(Coordinator& coordinator, const Vector2 cameraPos)
	{

		for (auto entity : this->m_Entites)
		{



		}

	}

};
