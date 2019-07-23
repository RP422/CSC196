#include "player.h"
#include "scene.h"

void Player::Update(float dt)
{
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) m_transform.rotation -= m_rotate * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) m_transform.rotation += m_rotate * dt;

	vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
	if (Core::Input::IsPressed(Core::Input::KEY_UP))
	{
		m_transform.translation += forward * m_speed * dt;
	}

	if (m_transform.translation.x > 1200.0f) m_transform.translation.x = 0.0f;
	if (m_transform.translation.x < 0.0f)   m_transform.translation.x = 1200.0f;
	if (m_transform.translation.y > 800.0f) m_transform.translation.y = 0.0f;
	if (m_transform.translation.y < 0.0f)   m_transform.translation.y = 800.0f;

	if (Core::Input::IsPressed(Core::Input::KEY_SPACE))
	{
		Actor* actor = m_scene->GetActorFactory()->Create("Missile_Spawner");
		actor->m_transform.translation = m_transform.translation;
		actor->m_transform.rotation = m_transform.rotation;

		m_scene->AddActor(actor);
		AudioSystem::Instance()->PlayAudio("Missile");
	}

	std::vector<Actor*> enemies = m_scene->GetActorsByTag("Enemy");

	for (Actor* enemy : enemies)
	{
		float distance = vector2::distance(enemy->m_transform.translation, m_transform.translation);

		if (distance <= 5.0f)
		{
			if (!enemy->IsFlaggedForDestruction())
			{
				FlagForDestruction();
				enemy->FlagForDestruction();
				break;
			}
		}
	}
}

bool Player::Load(const rapidjson::Value& value)
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
