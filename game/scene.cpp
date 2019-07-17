#include "scene.h"
#include "player.h"
#include "missile.h"

void Scene::Startup()
{
	ActorFactory::Instance()->Register("Missile", new Creator<Missile, Actor>());
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
	DestroyFlaggedActors();
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
				ActorFactory::Instance()->Register(actor->GetName(), new Spawner<Actor>(actor));
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

bool Scene::Load(const char* filename)
{
	rapidjson::Document document;
	json::load(filename, document);

	const rapidjson::Value& actors = document["actors"];
	const rapidjson::Value& spawners = document["spawners"];

	bool success = false;

	if (actors.IsArray())
	{
		if (LoadActors(actors))
		{
			if (spawners.IsArray())
			{
				if (LoadSpawners(spawners))
				{
					success = true;
				}
			}
		}
	}

	return success;
}

void Scene::AddActor(Actor* actor)
{
	actor->SetScene(this);
	m_actors.push_back(actor);
}

void Scene::DestroyFlaggedActors()
{
	for (Actor* actor : m_actors)
	{
		if (actor->IsFlaggedForDestruction())
		{
			m_actors.remove(actor);
			delete actor;
		}
	}
}