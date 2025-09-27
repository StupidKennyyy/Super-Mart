#include <map/map.hpp>
#include <assets/asset_manager.hpp>

void Map::InitializeGrid(const size_t GridWidth, const size_t GridHeight, Coordinator& coordinator)
{
	m_Grid_Height = GridHeight;
	m_Grid_Width = GridWidth;

	m_MapGrid.resize(m_Grid_Width);
	

	for (size_t x = 0; x < m_Grid_Width; x++)
	{
		m_MapGrid[x].resize(GridHeight);

		for (size_t y = 0; y < m_Grid_Height; y++)
		{

			Entity tile = coordinator.CreateEntity();

			m_MapGrid[x][y] = tile;

			TileType type;

			if (y < m_Grid_Height / 2)
			{
				type = TileType::Air;
				coordinator.AddComponent<Sprite>(tile,
					Sprite{
						.texture = g_Textures["AIR.png"]
					});
			}

			else
			{
				type = TileType::Ground;
				coordinator.AddComponent<Sprite>(tile,
					Sprite{
						.texture = g_Textures["GROUND.png"]
					});

			}

			coordinator.AddComponent<Transform>(tile,
				Transform{
					.Position = Vector2((float)(x * TileSize),(float)(y * TileSize)),
					.Size = Vector2((float)(TileSize), (float)(TileSize))
					
				});

			coordinator.AddComponent<Tile>(tile,
				Tile{
					.type = type
				});

			if (type == TileType::Ground)
				coordinator.AddComponent<Collider>(tile,
					Collider{
						.isSolid = true,
						.Size = {(float)TileSize, (float)TileSize},
						.tag = CollisionTag::Tile
					});

			else if (type == TileType::Air)
				coordinator.AddComponent<Collider>(tile,
					Collider{
						.isSolid = false,
						.Size = {(float)TileSize, (float)TileSize},
						.tag = CollisionTag::Tile
					});


		}
	}
}

void Map::LoadFromFile(Coordinator& coordinator, const std::filesystem::path& AssetsDir)
{

	std::filesystem::path mapPath = AssetsDir / "Maps" / "MAP1.txt";

	if (!std::filesystem::exists(mapPath))
	{
		std::cerr << "Map file not found: " << mapPath << std::endl;
		return;
	}

	std::ifstream file(mapPath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open map file: " << mapPath << std::endl;
		return;
	}

	std::cout << "Started Loading map" << std::endl;

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
		lines.push_back(line);

	}
	file.close();

	size_t GridWidth = lines.empty() ? 0 : lines[0].size();
	size_t GridHeight = lines.size();

	m_Grid_Width = GridWidth;
	m_Grid_Height = GridHeight;
	m_MapGrid.resize(GridWidth);
	for (size_t x = 0; x < m_Grid_Width; x++)
		m_MapGrid[x].resize(m_Grid_Height);

	for (size_t y = 0; y < m_Grid_Height; y++)
	{

		for (size_t x = 0; x < m_Grid_Width; x++)
		{

			Entity tile = coordinator.CreateEntity();
			m_MapGrid[x][y] = tile;

			TileType type;
			char c = lines[y][x];

			if (c == '#') // Ground
			{
				type = TileType::Ground;

				coordinator.AddComponent<Sprite>(tile,
					Sprite{
						.texture = g_Textures["GROUND.png"]
					});
			}

			else if (c == '0') // Air
			{
				type = TileType::Air;

				coordinator.AddComponent<Sprite>(tile,
				Sprite{
					.texture = g_Textures["AIR.png"]
				});

			}

			coordinator.AddComponent<Transform>(tile,
				Transform{
					.Position = Vector2((float)(x * TileSize),(float)(y * TileSize)),
					.Size = Vector2((float)(TileSize), (float)(TileSize))

				});

			coordinator.AddComponent<Tile>(tile,
				Tile{
					.type = type
				});

			coordinator.AddComponent<Collider>(tile, Collider{
				.isSolid = (type == TileType::Ground),
				.Size = { (float)TileSize, (float)TileSize },
				.tag = CollisionTag::Tile
			});

			
			//std::cout << (float)(x * TileSize) << (float)(y * TileSize) << std::endl;

		}
	}

	std::cout << "Loaded MAP1 from: " << mapPath << std::endl;

}

