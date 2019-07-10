// CSC196.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game.h"
#include "../core/core.h"
#include "../framework/factory.h"

#include <iostream>

random_real_t random;

class Actor
{

};
class Player : public Actor
{

};
class Enemy : public Actor
{

};

bool Update(float dt)
{
	bool quit = false;
	if (Core::Input::IsPressed(Core::Input::KEY_ESCAPE))
	{
		quit = true;
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	Game::Instance()->Draw(graphics);
}

int main()
{
	rapidjson::Document document;
	json::load("test.json", document);
	int i;
	json::get_int(document, "test_int", i);
	std::cout << i;

	Game::Instance()->Startup();

	Factory<Actor> factory;
	factory.Register("PLAYER", new Creator<Player, Actor>);
	factory.Register("ENEMY", new Creator<Enemy, Actor>);

	Actor* actor = factory.Create("PLAYER");
	delete actor;


	char window[] = "Game";
	Core::Init(window, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();

	Game::Instance()->Shutdown();
}