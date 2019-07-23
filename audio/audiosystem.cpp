#include "audiosystem.h"
#include "..\\core\assert.h"

void AudioSystem::Startup()
{
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	ASSERT_MSG(result == FMOD_OK, "Error creating FMOD system.");

	void* extradriverdata = nullptr;
	result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ASSERT_MSG(result == FMOD_OK, "Error initializing FMOD system.");
}

void AudioSystem::Shutdown()
{
	for (auto& sound : m_sounds)
	{
		ASSERT_MSG(sound.second->release() == FMOD_RESULT::FMOD_OK, "Could not properly release a sound.");
	}

	m_sounds.clear();

	ASSERT_MSG(m_system->close() == FMOD_RESULT::FMOD_OK, "Could not properly close FMOD.");
	
	delete m_system;
}

void AudioSystem::Update()
{
	m_system->update();
}

void AudioSystem::AddAudio(const std::string & key, const std::string & filename)
{
	if (m_sounds.find(key) == m_sounds.end())
	{
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (result == FMOD_OK)
		{
			m_sounds[key] = sound;
		}
	}
}

void AudioSystem::PlayAudio(const std::string & key, bool loop)
{
	// Find the sound
	auto iter = m_sounds.find(key);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* sound = iter->second;

		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		sound->setMode(mode);

		FMOD::Channel* chanel;
		ASSERT_MSG(m_system->playSound(sound, nullptr, false, &chanel) == FMOD_OK, "Could not play sound");
	}
}

void AudioSystem::RemoveAudio(const std::string & key)
{
	// Find the sound
	auto iter = m_sounds.find(key);
	if (iter != m_sounds.end())
	{
		iter->second->release();
		m_sounds.erase(key);
	}
}
