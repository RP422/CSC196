#pragma once

#include "../framework/singleton.h"
#include "../external/fmod/api/core/inc/fmod.hpp"

//#include <fmod.hpp>
#include <string>
#include <map>

class AudioSystem : public Singleton<AudioSystem>
{
public:
	void Startup();
	void Shutdown();

	void Update();

	void AddAudio(const std::string& key, const std::string& filename);
	void PlayAudio(const std::string& key, bool loop = false);
	void RemoveAudio(const std::string& key);

protected:
	AudioSystem() {}
	friend Singleton<AudioSystem>;

private:
	FMOD::System* m_system;
	std::map<std::string, FMOD::Sound*> m_sounds;
};
