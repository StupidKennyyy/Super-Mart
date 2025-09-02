#pragma once
#include <cstdint>

struct Vector2 {

	float x = 0.0f;
	float y = 0.0f;
};


struct Transform {

	Vector2 Position;

	Vector2 Size;
};

struct RigidBody {

	Vector2 Velocity;
};

struct Collider {

	bool isSolid;
};

struct Tile {

	int type;
};

struct Sprite {

	SDL_Texture* texture;
};

struct InputComponent {

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool jump = false;

};

struct CameraFollow {

	uint8_t CameraID;
};
