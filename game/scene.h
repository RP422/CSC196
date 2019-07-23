#pragma once

#include "actor.h"
#include "../framework/factory.h"
#include "../framework/singleton.h"
#include "../audio/audiosystem.h"

#include <list>

class Actor;
class Game;

// Yes, you can inherit from multiple classes. Cool, innit?
class ActorFactory : public Factory<Actor>
{
	
};

class Scene
{
public:
	Scene(Game* game) : m_game(game) {}
	~Scene() {}
	
	void Startup();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	bool Load(const char* filename);

	void AddActor(Actor* actor);

	Actor* GetActorByName(const std::string& name);
	std::vector<Actor*> GetActorsByTag(const std::string& tag);

	Game* GetGame() { return m_game; }
	ActorFactory * GetActorFactory() { return m_actorFactory; }

protected:
	bool LoadActors(const rapidjson::Value& value);
	bool LoadSpawners(const rapidjson::Value& value);

private:
	Game* m_game;
	ActorFactory* m_actorFactory;
	std::list<Actor*> m_actors;
	float m_spawnTimer;

private:
	void DestroyFlaggedActors();
};