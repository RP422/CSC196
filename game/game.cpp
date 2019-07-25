#include "game.h"
#include "../math/vector2.h"
#include "../renderer/color.h"

#include <random>

void Game::Startup()
{
	m_state = eState::INIT;

	AudioSystem::Instance()->Startup();
}

void Game::Shutdown()
{
	if (m_scene)
	{
		m_scene->Shutdown();
		delete m_scene;
	}

	AudioSystem::Instance()->Shutdown();
	AudioSystem::Destroy();
}

bool Game::Update(float dt)
{
	Actor* actor = nullptr;

	switch (m_state)
	{
	case Game::INIT:
		m_state = eState::TITLE;
		break;

	case Game::TITLE:
		if (Core::Input::IsPressed(Core::Input::KEY_SPACE))
		{
			m_state = eState::START_GAME;
		}
		break;

	case Game::START_GAME:
		m_scene = new Scene(this);
		m_scene->Startup();
		m_scene->Load("actor.json");
		
		actor = m_scene->GetActorFactory()->Create("Player_Spawner");
		m_scene->AddActor(actor);

		m_lives = 3;
		m_score = 0;
		m_state = eState::UPDATE_GAME;
		break;

	case Game::UPDATE_GAME:
		if (m_scene->GetActorByName("Player_Spawner") == nullptr)
		{
			m_lives--;

			if (m_lives == 0)
			{
				m_stateTimer = 4.0f;
				m_state = eState::GAME_OVER;
			}
			else
			{
				m_stateTimer = 2.0f;
				m_state = eState::RESPAWN;
			}
		}

		m_scene->Update(dt);
		break;

	case Game::RESPAWN:
		m_stateTimer -= dt;

		if (m_stateTimer <= 0.0f)
		{
			actor = m_scene->GetActorFactory()->Create("Player_Spawner");
			m_scene->AddActor(actor);
			m_state = eState::UPDATE_GAME;
		}

		m_scene->Update(dt);
		break;

	case Game::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f)
		{
			m_state = eState::RESET;
		}
		m_scene->Update(dt);
		break;

	case Game::RESET:
		m_scene->Shutdown();
		delete m_scene;
		m_scene = nullptr;

		m_state = eState::TITLE;
		break;

	default:
		break;
	}

	AudioSystem::Instance()->Update();

	bool quit = false;
	if (Core::Input::IsPressed(Core::Input::KEY_ESCAPE))
	{
		quit = true;
	}

	return quit;
}

void Game::Draw(Core::Graphics & graphics)
{
	color textColor = color::white;
	graphics.SetColor(textColor);

	switch (m_state)
	{
	case Game::TITLE:
		graphics.DrawString(569, 396, "Grabroids");
		break;
	case Game::UPDATE_GAME:
	case Game::RESPAWN:
		{
			std::string score = "Score: " + std::to_string(m_score) + "\nLives: " + std::to_string(m_lives);
			graphics.DrawString(20, 20, score.c_str());
		}
		m_scene->Draw(graphics);
		break;
	case Game::GAME_OVER:
		graphics.DrawString(569, 396, "Game Over");
		{
			std::string score = "Score: " + std::to_string(m_score) + "\nLives: " + std::to_string(m_lives);
			graphics.DrawString(20, 20, score.c_str());
		}
		m_scene->Draw(graphics);
		break;
	default:
		break;
	}

}
