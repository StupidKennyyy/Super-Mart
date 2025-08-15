#include <map.hpp>


void Map::InitializeGrid(const size_t GridWitdh, const size_t GridHeight)
{
	Grid_Height = GridHeight;
	Grid_Width = GridWitdh;

	MapGrid.resize(Grid_Width);

	for (size_t x = 0; x < Grid_Width; x++)
	{
		MapGrid[x].resize(Grid_Height);

		for (size_t y = 0; y < Grid_Height; y++)
		{
			if (y < Grid_Height / 2)
				MapGrid[x][y].Type = TileType::Air;
			else
				MapGrid[x][y].Type = TileType::Ground;
		}
	}
}

void Map::RenderGrid(SDL_Renderer* renderer, Camera& camera) 
{

	for (size_t x = 0; x < Grid_Width; x++)
	{

		for (size_t y = 0; y < Grid_Height; y++)
		{

			float drawX = (x * TileSize + camera.x) * camera.zoom;
			float drawY = (y * TileSize + camera.y) * camera.zoom;

			SDL_FRect rect = { drawX, drawY, TileSize, TileSize };

			switch (MapGrid[x][y].Type)
			{
			case TileType::Air:
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				//std::cout << "AIR" << std::endl;
				break;
			case TileType::Ground:
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				//std::cout << "GROUND" << std::endl;
				break;
			}

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}