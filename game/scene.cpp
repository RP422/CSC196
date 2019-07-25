#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "emitter.h"
#include "../effects/particle_system.h"

void Scene::Startup()
{
	m_particleSystem = new ParticleSystem(2000);

	m_actorFactory = new ActorFactory;
	m_actorFactory->Register("Player", new Creator<Player, Actor>());
	m_actorFactory->Register("Enemy", new Creator<Enemy, Actor>());
	m_actorFactory->Register("Missile", new Creator<Missile, Actor>());
	m_actorFactory->Register("Emitter", new Creator<Emitter, Actor>());

	AudioSystem::Instance()->AddAudio("Missile", "audio/missile.wav");
	AudioSystem::Instance()->AddAudio("Explosion", "audio/explosion.wav");
}

void Scene::Shutdown()
{
	// Typically you want to reverse the order of creation in here to avoid dependency bs.
	for (Actor* actor : m_actors)
	{
		delete actor;
	}

	delete m_actorFactory;
	delete m_particleSystem;
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

	m_particleSystem->Update(dt);

	DestroyFlaggedActors();
}

void Scene::Draw(Core::Graphics& graphics)
{
	for (Actor* actor : m_actors)
	{
		actor->Draw(graphics);
	}
	m_particleSystem->Draw(graphics);
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

	const rapidjson::Value& spawners = document["spawners"];

	bool success = spawners.IsArray() && LoadSpawners(spawners);

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
			r_actor = actor;
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

		delete front;
	}
}