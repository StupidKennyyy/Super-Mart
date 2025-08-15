#pragma once

struct Vector2 {

	float x, y;
};


struct Transform {

	Vector2 Position{ 0,0 };

	struct Size {
		float width, height;
	};


	Size Size{ 0,0 };

	Transform() {};

};


