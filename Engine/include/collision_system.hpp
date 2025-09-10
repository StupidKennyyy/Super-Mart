#include <SDL3/SDL.h>
#include <ecs.hpp>
#include <iterator>
#include <components.hpp>
#include <iostream>
#include <map.hpp>

class CollisionSystem : public System {

public:

	void Update(Coordinator& coordinator, Map& map)
	{
		Entity player = NULLENTITY;
		for (auto& entity : m_Entites)
		{
			auto& col = coordinator.GetComponent<Collider>(entity);
			if (col.tag == CollisionTag::Player)
				player = entity;
		}

		auto& PlayerTransform = coordinator.GetComponent<Transform>(player);

		auto& PlayerRigidBody = coordinator.GetComponent<RigidBody>(player);

		SDL_FRect PlayerRect = {
			PlayerTransform.Position.x,
			PlayerTransform.Position.y,
			PlayerTransform.Size.x,
			PlayerTransform.Size.y
		};

		SDL_FRect FoorSensor = {
			PlayerTransform.Position.x + 2,
			PlayerTransform.Position.y + 40,
			36,
			2
		};

		int tx = static_cast<int>(PlayerTransform.Position.x / map.TileSize);
		int ty = static_cast<int>(PlayerTransform.Position.y / map.TileSize);

		auto& v_MapGrid = map.GetMap();
		
		Vector2 Correction = { 0,0 };
		
		// Position correction

		for (int y = ty - 1; y <= ty + 1; y++) {

			for (int x = tx - 1; x <= tx + 1; x++) {

				if (x < 0 || x >= v_MapGrid.size() || y < 0 || y >= v_MapGrid[0].size()) {
					continue;
				}
				PlayerRigidBody.Grounded = false;

				auto& tile = v_MapGrid[x][y];

				auto& TileCollider = coordinator.GetComponent<Collider>(tile);

				if (!(TileCollider.isSolid))
				{
					continue;
				}
				
				auto& TileTransform = coordinator.GetComponent<Transform>(tile);

				SDL_FRect TileRect = {
					TileTransform.Position.x,
					TileTransform.Position.y,
					TileTransform.Size.x,
					TileTransform.Size.y
				};

				SDL_FRect Result;


				if (SDL_GetRectIntersectionFloat(&PlayerRect, &TileRect, &Result))
				{
					if (Result.w < Result.h)
						Correction.x += (PlayerRect.x < TileRect.x ? -Result.w : Result.w);
					else
						Correction.y += (PlayerRect.y < TileRect.y ? -Result.h : Result.h);
				}
				

					
			}

		}
		
		PlayerTransform.Position += Correction;

		int y = ty + 1;

		for (int x = tx - 1; x <= tx + 1; x++)
		{
			if (x < 0 || x >= v_MapGrid.size() || y < 0 || y >= v_MapGrid[0].size()) {
			continue;
			}
			
			auto& tile = v_MapGrid[x][y];

			auto& TileCollider = coordinator.GetComponent<Collider>(tile);

			if (!(TileCollider.isSolid))
			{
				continue;
			}

			auto& TileTransform = coordinator.GetComponent<Transform>(tile);

			SDL_FRect TileRect = {
				TileTransform.Position.x,
				TileTransform.Position.y,
				TileTransform.Size.x,
				TileTransform.Size.y
			};

			if (SDL_HasRectIntersectionFloat(&FoorSensor, &TileRect))
			{
				PlayerRigidBody.Grounded = true;
			}
			else
			{
				PlayerRigidBody.Grounded = false;
			}


		}

	}

};