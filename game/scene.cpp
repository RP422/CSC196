#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "missile.h"

void Scene::Startup()
{
	m_actorFactory = new ActorFactory;
	m_actorFactory->Register("Player", new Creator<Player, Actor>());
	m_actorFactory->Register("Enemy", new Creator<Enemy, Actor>());
	m_actorFactory->Register("Missile", new Creator<Missile, Actor>());

	AudioSystem::Instance()->AddAudio("Missile", "audio/missile.wav");
}

void Scene::Shutdown()
{
	delete m_actorFactory;
	for (Actor* actor : m_actors)
	{
		delete actor;
	}
}

void Scene::Update(float dt)
{
	m_spawnTimer += dt;
	if (m_spawnTimer >= 4)
	{
		// Do Stuff
		m_spawnTimer = 0;

		Actor* actor = m_actorFactory->Create("Enemy_Spawner");

		random_real_t random;
		actor->m_transform.translation = vector2(random(1200.0f), random(800.0f));
		actor->m_transform.rotation = random(math::TWO_PI);
		AddActor(actor);
	}

	for (Actor* actor : m_actors)
	{
		actor->Update(dt);
	}

	DestroyFlaggedActors();
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
			Actor* actor = m_actorFactory->Create(type);
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
			Actor* actor = m_actorFactory->Create(type);
			if (actor && actor->Load(actor_value))
			{
				m_actorFactory->Register(actor->GetName(), new Spawner<Actor>(actor));
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

Actor * Scene::GetActorByName(const std::string & name)
{
	Actor* r_actor = nullptr;

	for (Actor* actor : m_actors)
	{
		if (actor->GetName() == name)
		{
			actor = r_actor;
			break;
		}
	}

	return r_actor;
}

std::vector<Actor*> Scene::GetActorsByTag(const std::string & tag)
{
	std::vector<Actor*>actors;

	for (Actor* actor : m_actors)
	{
		if (actor->GetTag() == tag)
		{
			actors.push_back(actor);
		}
	}

	return actors;
}

void Scene::DestroyFlaggedActors()
{
	std::list<Actor*> flaggedActors;

	for (Actor* actor : m_actors)
	{
		if (actor->IsFlaggedForDestruction())
		{
			flaggedActors.push_back(actor);
		}
	}

	while (flaggedActors.size() > 0)
	{
		Actor* front = flaggedActors.front();
		m_actors.remove(front);

		flaggedActors.pop_front();
	}
}