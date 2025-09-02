#pragma once
#include <ecs.hpp>
#include <components.hpp>


class MovementSystem : public System {

public:

	void Update(Coordinator& coordinator)
	{

		for (Entity entity : m_Entites)
		{

			auto& input = coordinator.GetComponent<InputComponent>(entity);
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& rb = coordinator.GetComponent<RigidBody>(entity);
			
			rb.Velocity = { 0,0 };

			if (input.up) rb.Velocity.y = -1.f;
			if (input.down) rb.Velocity.y = 1.f;
			if (input.right) rb.Velocity.x = 1.f;
			if (input.left) rb.Velocity.x = -1.f;

			transform.Position.x += rb.Velocity.x * 1.f;
			transform.Position.y += rb.Velocity.y * 1.f;

		}

	}


};