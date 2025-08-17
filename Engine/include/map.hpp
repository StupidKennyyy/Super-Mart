#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "render_system.hpp"
#include "components.hpp"
#include "Tile.hpp"
#include "camera.hpp"

class Map {


private:

	size_t Grid_Width;
	size_t Grid_Height;
	const int TileSize = 16;

	std::vector<std::vector<Tile>> MapGrid;

public:

	void InitializeGrid(const size_t GridWitdh, const size_t GridHeight);
	void RenderGrid(SDL_Renderer* renderer, const Vector2& CameraPosition);

};

