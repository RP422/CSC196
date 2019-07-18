// CSC196.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game.h"
#include "../core/core.h"
#include "../framework/factory.h"

#include <iostream>

random_real_t random;

//class GameObject
//{
//
//};
//class Player : public GameObject
//{
//
//};
//class Enemy : public GameObject
//{
//
//};

bool Update(float dt)
{
	bool quit = false;
	if (Game::Instance()->Update(dt))
	{
		quit = true;
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	Game::Instance()->Draw(graphics);
}

void JsonLoadTest()
{
	rapidjson::Document document;
	json::load("test.json", document);
	int i;
	json::get_int(document, "test_int", i);
	std::cout << i << std::endl;
}

int main()
{
	Game::Instance()->Startup();

	//Factory<GameObject> factory;
	//factory.Register("PLAYER", new Creator<Player, GameObject>);
	//factory.Register("ENEMY", new Creator<Enemy, GameObject>);

	//GameObject* actor = factory.Create("PLAYER");
	//delete actor;

	char window[] = "Game";
	Core::Init(window, 1200, 800);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();

	Game::Instance()->Shutdown();
	Game::Instance()->Destroy();
}