#include "Game.h"
#include <iostream>
#include "kecs/KECS.h"
#include "rendering/KRenderer.h"
#include "Components/c_transform.h"
#include "Tags.h"
#include "Components/c_input.h"
#include "Components/c_physics.h"
#include "KTime.h"
#include "systems/RenderSystem.h"
#include "systems/InputSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/BoxMovementSystem.h"
#include "InputManager.h"
#include "net/Client.h"

Game::~Game()
{
	delete inputSystem;
	delete renderSystem;
	delete physicsSystem;
	delete boxMovementSystem;
	delete client;
	delete kRenderer;
}


void Game::Run(){

	EntityManager::SetUpComponents<Transform, UserInput, Physics>();
	EntityManager::SetUpTags<Player>();

	std::cout<<"Starting game"<<std::endl;

	Entity player = EntityManager::CreateEntity();

	UserInput* playerInput = EntityManager::AddComponent<UserInput>(player);


	Transform* playerTrans = EntityManager::AddComponent<Transform>(player);
	if(playerTrans != nullptr)
	{
		playerTrans->position.SetValues(100, 100);
	}

	Physics* playerPhysics = EntityManager::AddComponent<Physics>(player);
	if (playerPhysics != nullptr)
	{
		playerPhysics->maxSpeed = 300;
		playerPhysics->friction = 700;
	}


	while (!quit)
	{
		KTime::CalculateDeltaTime();
		InputManager::GetInstance().UpdateInput();
		quit = InputManager::GetInstance().ShouldQuit();
		inputSystem->GetUserInput();
		boxMovementSystem->UpdateBoxMovement();
		physicsSystem->ApplyPhysics();
		renderSystem->DrawPlayers(*kRenderer);
		renderSystem->DrawToScreen(*kRenderer);
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

bool Game::SetUp(int screenWidth, int screenHeight) {
	bool success = true;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	client = new Client();

	std::cout<<"Enter port to receive packets on: ";
	std::string portToOpenInput;
	std::cin >> portToOpenInput;
	std::cout<<"Input IP and Port in aaaa.bbbb.cccc.dddd:xxxx format: ";
	std::string ipInput;
	std::cin >> ipInput;
	std::cin.ignore();

	unsigned int networkId;
	if (client->ConnectToServer(networkId, portToOpenInput, ipInput))
	{
		std::cout<<"Message to send: ";
		std::string message;
		getline(std::cin, message);

		client->SendMessage(networkId, message);
		
		kRenderer = new KRenderer();
		if (kRenderer->Initialize(screenWidth, screenHeight))
		{
			//Initialize systems
			renderSystem = new RenderSystem();
			inputSystem = new InputSystem();
			physicsSystem = new PhysicsSystem();
			boxMovementSystem = new BoxMovementSystem();
		}
		else
		{
			std::cout<<"Could not initialize renderer"<<std::endl;
			success = false;
		}
	}
	else
	{
		std::cout<<"Could not connect to server"<<std::endl;
		success = false;
	}

	return success;
}
