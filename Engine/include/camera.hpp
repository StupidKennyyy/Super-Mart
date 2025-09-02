#pragma once
#include <components.hpp>
#include <input.hpp>


class CameraManager {

private:

	Transform transform;
	float zoom = 1.f;
	RigidBody rb;
	float speed = 1.0f;
	Input& input;

	Entity follow;

public:

	CameraManager(Input& input) : input(input) {}

	void FollowEntity(Entity entity)
	{
		follow = entity;
	}

	void Update()
	{
		
		rb.Velocity = { 0,0 };

		if (input.isKeyDown(SDL_SCANCODE_W)) rb.Velocity.y = 1;
		if (input.isKeyDown(SDL_SCANCODE_S)) rb.Velocity.y = -1;
		if (input.isKeyDown(SDL_SCANCODE_A)) rb.Velocity.x = 1;
		if (input.isKeyDown(SDL_SCANCODE_D)) rb.Velocity.x = -1;

		transform.Position.x += rb.Velocity.x * speed;
		transform.Position.y += rb.Velocity.y * speed;

	}

	void SetPosition(Vector2 position)
	{
		transform.Position = position;
	}

	const Vector2 GetPosition() const
	{
		return transform.Position;
	}

};