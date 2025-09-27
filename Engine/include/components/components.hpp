#pragma once
#include <cstdint>
#include <SDL3/SDL.h>
#include <cmath>

struct Vector2 {

	float x = 0.0f;
	float y = 0.0f;

    float Length() const
    {
        return std::sqrtf(x * x + y * y);
    }

    void Normalize()
    {
        float len = Length();

        if (len != 0) {
            x /= len;
            y /= len;
        }
    }

    // Addition
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Subtraction
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Scalar multiplication
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Scalar division
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }
    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Optional: equality
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }
};


struct Transform {

	Vector2 Position;

	Vector2 Size;
};

struct RigidBody {

	Vector2 Velocity;
    Vector2 Acceleration;
    bool Grounded = false;
};

enum class CollisionTag {
	None,
	Player,
	Enemy,
	Tile
};

struct Collider {

	bool isSolid;
	Vector2 Size;
	CollisionTag tag = CollisionTag::None;
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
