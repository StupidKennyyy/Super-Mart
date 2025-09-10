#include <SDL3/SDL.h>
#include <ecs.hpp>
#include <iterator>
#include <components.hpp>
#include <iostream>

class CollisionSystem : public System {

public:

	void Update(Coordinator& coordinator)
	{

		for (auto& entityA : m_Entites)
		{

			auto& colA = coordinator.GetComponent<Collider>(entityA);

			if (colA.tag != CollisionTag::Player)
				continue;

			auto& transA = coordinator.GetComponent<Transform>(entityA);

			for (auto& entityB : m_Entites)
			{

				if (entityA == entityB)
					continue;

				auto& colB = coordinator.GetComponent<Collider>(entityB);

				if (!CouldCollide(colA.tag, colB.tag))
					continue;

				std::cout << transA.Position.x << ", " << transA.Position.y << std::endl;


			}

		}
	

	}

private:

	bool CouldCollide(CollisionTag& a, CollisionTag& b)
	{
		if (a == CollisionTag::None || b == CollisionTag::None) return false;

		if (a == CollisionTag::Tile && b == CollisionTag::Tile) return false;

		if ((a == CollisionTag::Player && b == CollisionTag::Tile) || (a == CollisionTag::Tile && b == CollisionTag::Player)) return true;

		return false;
	}


};