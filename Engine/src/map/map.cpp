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

