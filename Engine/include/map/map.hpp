#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <components/Tile.hpp>
#include <components/components.hpp>
#include <ecs/ecs.hpp>
#include <filesystem>
#include <fstream>

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
	void LoadFromFile(Coordinator& coordinator, const std::filesystem::path& MapPath);

};

