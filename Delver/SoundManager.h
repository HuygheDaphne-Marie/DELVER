#pragma once

#include "SoundEffect.h"
#include "SoundStream.h"
#include <unordered_map>

class SoundManager
{
public:
	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;
	~SoundManager();

	static SoundManager* GetInstance();

	SoundEffect* GetSoundEffect(const std::string& soundFile);
	SoundStream* GetSoundStream(const std::string& soundFile);

	void PlaySoundEffect(SoundEffect* effect);
	void PlaySoundStream(SoundStream* stream);

	int GetEffectsVolume() const;
	void SetEffectsVolume(int volume);

	int GetStreamVolume() const;
	void SetStreamVolume(int volume);


private:
	std::unordered_map<std::string, SoundEffect*> m_SoundEffects;
	std::unordered_map<std::string, SoundStream*> m_SoundStreams;

	SoundStream* m_pCurrentlyPlayingStream;

	int m_EffectVolume;
	int m_StreamVolume;

	SoundManager();
};

