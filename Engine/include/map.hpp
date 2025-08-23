#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "renderSystems.hpp"
#include "components.hpp"
#include "Tile.hpp"
#include "camera.hpp"
#include <ecs.hpp>
#include <asset_manager.hpp>

class Map {


private:

	size_t Grid_Width;
	size_t Grid_Height;
	const int TileSize = 16;

	std::vector<std::vector<Entity>> MapGrid;

public:

	void InitializeGrid(const size_t GridWitdh, const size_t GridHeight, Coordinator& coordinator);

};

