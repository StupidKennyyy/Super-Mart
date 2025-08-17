#pragma once

struct Vector2 {

	float x, y;
};


struct Transform {

	Vector2 Position;

	Vector2 Size;
};

struct RigidBody {

	Vector2 Velocity;

};
