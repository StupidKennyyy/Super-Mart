#pragma once
#include <include.hpp>
#include <iostream>
#include <algorithm>

class MovementSystem : public System {

private:

	float speed = 10.f;
	float accel = 1000.f;
	float decel = 800.f;
	float jump = 1000.0f;

public:

	void Update(Coordinator& coordinator, float deltaTime)
	{

		for (Entity entity : m_Entites)
		{

			auto& input = coordinator.GetComponent<InputComponent>(entity);
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& rb = coordinator.GetComponent<RigidBody>(entity);
			
			float targetVelX = 0.0f;

			if (input.right) targetVelX = speed;
			if (input.left) targetVelX = -speed;

			if (rb.Velocity.x < targetVelX)
				rb.Velocity.x = std::min(rb.Velocity.x + accel * deltaTime, targetVelX);
			else if (rb.Velocity.x > targetVelX)
				rb.Velocity.x = std::max(rb.Velocity.x - accel * deltaTime, targetVelX);

			if (targetVelX == 0.0f)
			{
				if (rb.Velocity.x > 0)
					rb.Velocity.x = std::max(0.0f, rb.Velocity.x - decel * deltaTime);
				else if (rb.Velocity.x < 0)
					rb.Velocity.x = std::min(0.0f, rb.Velocity.x + decel * deltaTime);
			}

			float targetVelY = 0.0f;

			if (input.up) targetVelY = -jump;
			if (input.down) targetVelY = speed;

			if (rb.Velocity.y < targetVelY)
				rb.Velocity.y = std::min(rb.Velocity.y + accel * deltaTime, targetVelY);
			else if (rb.Velocity.y > targetVelY)
				rb.Velocity.y = std::max(rb.Velocity.y - accel * deltaTime, targetVelY);

			if (targetVelY == 0.0f)
			{
				if (rb.Velocity.y > 0)
					rb.Velocity.y = std::max(0.0f, rb.Velocity.y - decel * deltaTime);
				else if (rb.Velocity.y < 0)
					rb.Velocity.y = std::min(0.0f, rb.Velocity.y + decel * deltaTime);
			}


			transform.Position.x += rb.Velocity.x;
			transform.Position.y += rb.Velocity.y;



		}

	}


};