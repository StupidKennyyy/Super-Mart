#pragma once

#include <components/components.hpp>
#include <SDL3/SDL.h>
#include <ecs/ecs.hpp>
#include <camera/camera.hpp>

class CameraSystem : public System {

public:

	void Update(CameraManager& camManager, Coordinator& coordinator)
	{

		for (auto& entity : m_Entites)
		{
			auto& follow = coordinator.GetComponent<CameraFollow>(entity);
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& cam = camManager.GetData(follow.CameraID);

			cam.Position.x = transform.Position.x - 400 + 10;
			cam.Position.y = transform.Position.y - 300 + 10;
		}

	}

};
