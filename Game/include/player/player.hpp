#include <include.hpp>

class Player {

private:

	Entity player;

public:

	Entity GetEntity() const
	{
		return player;
	}

	void CreatePlayer(Transform transform, Coordinator& coordinator, CameraManager cameraManager)
	{
		player = coordinator.CreateEntity();

		coordinator.AddComponent<Transform>(player, transform);

		coordinator.AddComponent<Sprite>(player,
			Sprite{
				.texture = g_Textures["PLAYER.png"]
			});
		coordinator.AddComponent<RigidBody>(player, RigidBody{.Acceleration = 3000.f});

		coordinator.AddComponent<InputComponent>(player, InputComponent{});

		coordinator.AddComponent<CameraFollow>(player,
			CameraFollow{
				.CameraID = cameraManager.GetActiveCamera()
			});

		coordinator.AddComponent<Collider>(player,
			Collider{
				.isSolid = true,
				.Size = transform.Size,
				.tag = CollisionTag::Player
			});

	}

	void DeletePlayer(Coordinator coordinator)
	{
		coordinator.DestroyEntity(player);
	}

};