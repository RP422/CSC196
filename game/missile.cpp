#include "missile.h"
#include "scene.h"
#include "game.h"

void Missile::Update(float dt)
{
	vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
	m_transform.translation += forward * m_speed * dt;

	m_lifetime -= dt;

	if (m_lifetime <= 0)
	{
		FlagForDestruction();
	}

	//// With Screen Wrapping
	//if (m_transform.translation.x > 1200.0f) m_transform.translation.x = 0.0f;
	//if (m_transform.translation.x < 0.0f)   m_transform.translation.x = 1200.0f;
	//if (m_transform.translation.y > 800.0f) m_transform.translation.y = 0.0f;
	//if (m_transform.translation.y < 0.0f)   m_transform.translation.y = 800.0f;

	// Without Screen Wrapping
	if (m_transform.translation.x > 1200.0f)
	{ 
		FlagForDestruction();	
	}
	if (m_transform.translation.x < 0.0f)
	{
		FlagForDestruction();
	}
	if (m_transform.translation.y > 800.0f)
	{
		FlagForDestruction();
	}
	if (m_transform.translation.y < 0.0f)
	{
		FlagForDestruction();
	}

	std::vector<Actor*> enemies = m_scene->GetActorsByTag("Enemy");

	for (Actor* enemy : enemies)
	{
		float distance = vector2::distance(enemy->m_transform.translation, m_transform.translation);

		if (distance <= 15.0f)
		{
			if (!enemy->IsFlaggedForDestruction())
			{
				m_scene->GetGame()->IncrementScore(100);
				FlagForDestruction();
				enemy->FlagForDestruction();

				Actor* actor;

				actor = m_scene->GetActorFactory()->Create("Explosion_Spawner");
				actor->m_transform.translation = enemy->m_transform.translation;
				actor->m_transform.rotation = enemy->m_transform.rotation;

				AudioSystem::Instance()->PlayAudio("Explosion");
				m_scene->AddActor(actor);

				break;
			}
		}
	}
}

bool Missile::Load(const rapidjson::Value& value)
{
	bool success = Actor::Load(value);

	if (success)
	{
		success = json::get_float(value, "speed", m_speed);

		if (success)
		{
			success = json::get_float(value, "rotate", m_rotate);
		}
	}

	return success;
}
