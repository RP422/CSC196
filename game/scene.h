#pragma once

#include "actor.h"
#include "../framework/factory.h"
#include "../framework/singleton.h"

#include <list>

class Actor;

// Yes, you can inherit from multiple classes. Cool, innit?
class ActorFactory : public Factory<Actor>, public Singleton<ActorFactory>
{
protected:
	ActorFactory() {}
	friend class Singleton<ActorFactory>;
};

class Scene
{
public:
	Scene() {}
	~Scene() {}
	
	void Startup();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	bool Load(const char* filename);

	void AddActor(Actor* actor);

protected:
	bool LoadActors(const rapidjson::Value& value);
	bool LoadSpawners(const rapidjson::Value& value);

private:
	std::list<Actor*> m_actors;

	void DestroyFlaggedActors();
};