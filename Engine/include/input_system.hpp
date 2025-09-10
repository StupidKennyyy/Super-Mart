#pragma once
#include <ecs.hpp>
#include <input.hpp>


class InputSystem : public System {

public:

	void Update(Coordinator& coordinator, Input& input_)
	{

		for (Entity entity : this->m_Entites)
		{

			auto& input = coordinator.GetComponent<InputComponent>(entity);

			input.up = input_.isKeyDown(SDL_SCANCODE_W);
			input.down = input_.isKeyDown(SDL_SCANCODE_S);
			input.right = input_.isKeyDown(SDL_SCANCODE_D);
			input.left = input_.isKeyDown(SDL_SCANCODE_A);
			input.jump = input_.isKeyDown(SDL_SCANCODE_SPACE);

		}

	}

};