#pragma once
#include <include.hpp>
#include <iostream>
#include <algorithm>

class MovementSystem : public System {

private:

	float speed = 500.f;
	float AccelerationRate = 3000.f;
	float DecelerationRate = 800.f;
	float BrakeRate = 6000.f;

public:

	void Update(Coordinator& coordinator, float& deltaTime)
	{

		for (Entity entity : m_Entites)
		{

			auto& input = coordinator.GetComponent<InputComponent>(entity);
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& rb = coordinator.GetComponent<RigidBody>(entity);
			
			rb.Acceleration = { 0,0 };
			rb.Acceleration.y += 350.f;

			Vector2 Velocity = rb.Velocity;
			Vector2 TargetVelocity = Vector2(0, 0);

			TargetVelocity.x += input.right * speed;
			TargetVelocity.x -= input.left * speed;

			TargetVelocity.y -= input.up * speed;
			TargetVelocity.y += input.down * speed;

			Vector2 VelocityDifference = TargetVelocity - Velocity;

			Vector2 Rate = { 0,0 };

			if (TargetVelocity.x == 0)
				Rate.x = DecelerationRate;
			else if ((Velocity.x * TargetVelocity.x) > 0)
				Rate.x = AccelerationRate;
			else
				Rate.x = BrakeRate;

			if (TargetVelocity.y == 0)
				Rate.y = DecelerationRate;
			else if ((Velocity.y * TargetVelocity.y) > 0)
				Rate.y = AccelerationRate;
			else
				Rate.y = BrakeRate;

			rb.Acceleration.x += std::clamp(VelocityDifference.x, -Rate.x, Rate.x);
			rb.Acceleration.y += std::clamp(VelocityDifference.y, -Rate.y, Rate.y);

			rb.Velocity += rb.Acceleration;

			transform.Position += rb.Velocity * deltaTime;

		}

	}


};