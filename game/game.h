#pragma once

#include "scene.h"
#include "../core/core.h"
#include "../external/core/include/core.h"

class Game
{
public:
	enum eState
	{
		INIT,
		TITLE,
		START_GAME,
		UPDATE_GAME,
		GAME_OVER,
		RESET
	};

public:
	Game() {}

	void Startup();
	void Shutdown();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	int GetScore() { return m_score; }
	void SetScore(int score) { m_score = score; }
	void IncrementScore(int score) { m_score += score; }

	int GetLives() { return m_lives; }
	void SetLives(int lives) { m_lives = lives; }
	void LoseLife() { m_lives -= 1; }

private:
	Scene* m_scene;
	random_real_t m_random;

	int m_score;
	int m_lives;

	eState m_state;
	float m_stateTimer;
};