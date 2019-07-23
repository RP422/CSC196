// CSC196.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game.h"
#include "../core/core.h"
#include "../framework/factory.h"

#include <iostream>

Game* game;

bool Update(float dt)
{
	return game->Update(dt);
}

void Draw(Core::Graphics& graphics)
{
	game->Draw(graphics);
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
	game = new Game();
	game->Startup();

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

	game->Shutdown();
}