#include "scene.h"
#include "player.h"

void Scene::Startup()
{
	ActorFactory::Instance()->Register("Actor", new Creator<Actor, Actor>());
	ActorFactory::Instance()->Register("Player", new Creator<Player, Actor>());
}

void Scene::Shutdown()
{
	ActorFactory::Destroy();
	for (Actor* actor : m_actors)
	{
		delete actor;
	}
}

void Scene::Update(float dt)
{
	for (Actor* actor : m_actors)
	{
		actor->Update(dt);
	}
}

void Scene::Draw(Core::Graphics& graphics)
{
	for (Actor* actor : m_actors)
	{
		actor->Draw(graphics);
	}
}

// Take a good look at this method
bool Scene::LoadActors(const rapidjson::Value& value)
{
	bool success = true;

	for (rapidjson::SizeType i = 0; success && i < value.Size(); i++)
	{
		const rapidjson::Value& actor_value = value[i];
		std::string type;
		if (json::get_string(actor_value, "type", type))
		{
			Actor* actor = ActorFactory::Instance()->Create(type);
			if (actor && actor->Load(actor_value))
			{
				AddActor(actor);
			}
			else
			{
				success = false;
			}
		}
		else
		{
			success = false;
		}
	}

	return success;
}

bool Scene::LoadSpawners(const rapidjson::Value & value)
{
	return false;
}

bool Scene::Load(const char* filename)
{
	rapidjson::Document document;
	json::load(filename, document);

	const rapidjson::Value& actors = document["actors"];

	bool success = actors.IsArray();

	if (success)
	{
		success = LoadActors(actors);
	}

	return success;
}

void Scene::AddActor(Actor* actor)
{
	m_actors.push_back(actor);
}
