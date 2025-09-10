#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "render_systems.hpp"
#include "components.hpp"
#include "Tile.hpp"
#include "camera.hpp"
#include <ecs.hpp>
#include <asset_manager.hpp>

using MapGrid = std::vector<std::vector<Entity>>;

class Map {

public:

	const int TileSize = 40;

private:

	size_t m_Grid_Width = 0;
	size_t m_Grid_Height = 0;

	MapGrid m_MapGrid;

public:
	
	const std::vector<std::vector<Entity>>& GetMap() const { return m_MapGrid; }

	void InitializeGrid(const size_t GridWitdh, const size_t GridHeight, Coordinator& coordinator);

};

