#include "player.h"
#include "scene.h"

void Player::Update(float dt)
{
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) m_transform.rotation -= 0.1f;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) m_transform.rotation += 0.1f;

	vector2 forward = vector2::rotate(vector2(0.0f, 1.0f), m_transform.rotation);
	if (Core::Input::IsPressed(Core::Input::KEY_UP))
	{
		m_transform.translation += forward * 10.0f;
	}

	if (m_transform.translation.x > 800.0f) m_transform.translation.x = 0.0f;
	if (m_transform.translation.x < 0.0f)   m_transform.translation.x = 800.0f;
	if (m_transform.translation.y > 600.0f) m_transform.translation.y = 0.0f;
	if (m_transform.translation.y < 0.0f)   m_transform.translation.y = 600.0f;
}
