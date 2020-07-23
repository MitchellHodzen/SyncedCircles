#pragma once

class InputSystem;
class RenderSystem;
class PhysicsSystem;
class BoxMovementSystem;
class KRenderer;
class Client;

class Game
{
public:
	bool SetUp(int screenWidth, int screenHeight);
	void Run();
	~Game();
private:

	int screenWidth;
	int screenHeight;
	bool quit = false;

	InputSystem* inputSystem;
	RenderSystem* renderSystem;
	PhysicsSystem* physicsSystem;
	BoxMovementSystem* boxMovementSystem;
	KRenderer* kRenderer;
	Client* client;
};

