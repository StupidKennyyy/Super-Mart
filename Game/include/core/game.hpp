#include <player/player.hpp>
#include <include.hpp>
#include <systems/camera_system.hpp>
#include <systems/collision_system.hpp>
#include <systems/input_system.hpp>
#include <systems/movement_system.hpp>
#include <systems/render_systems.hpp>



class Game {

public:
	
	Player player;

	Engine engine;

	Map map;

	Input input;

	SDL_Renderer* renderer;

	std::shared_ptr<TileRenderSystem> tileRenderSys;
	std::shared_ptr<SpriteRenderSystem> spriteRenderSys;
	std::shared_ptr<InputSystem> inputSys;
	std::shared_ptr<MovementSystem> movementSys;
	std::shared_ptr<CameraSystem> cameraSys;
	std::shared_ptr<CollisionSystem> collisionSys;


public:

	void Init(const char* title, int width, int height);

	void Run();

	void DeInit();

	void InitializeGameSystems(Coordinator& coordinator);

};