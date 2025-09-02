#include <components.hpp>
#include <ecs.hpp>
#include <SDL3/SDL.h>
#include <asset_manager.hpp>

class Player {

private:

	Entity player;

public:

	Entity GetEntity() const
	{
		return player;
	}

	void CreatePlayer(Transform transform, Coordinator& coordinator)
	{
		player = coordinator.CreateEntity();

		coordinator.AddComponent<Transform>(player, transform);
		coordinator.AddComponent<Sprite>(player,
			Sprite{
				.texture = g_Textures["PLAYER.png"]
			});
		coordinator.AddComponent<RigidBody>(player, RigidBody{});
		coordinator.AddComponent<InputComponent>(player, InputComponent{});

	}

	void DeletePlayer(Coordinator coordinator)
	{
		coordinator.DestroyEntity(player);
	}

};