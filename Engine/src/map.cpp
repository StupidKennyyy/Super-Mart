#include <map.hpp>
#include <asset_manager.hpp>


void Map::InitializeGrid(const size_t GridWidth, const size_t GridHeight, Coordinator& coordinator)
{
	Grid_Height = GridHeight;
	Grid_Width = GridWidth;
	

	for (size_t x = 0; x < Grid_Width; x++)
	{

		for (size_t y = 0; y < Grid_Height; y++)
		{
			Entity tile = coordinator.CreateEntity();

			TileType type;

			if (y < Grid_Height / 2)
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

		}
	}
}

