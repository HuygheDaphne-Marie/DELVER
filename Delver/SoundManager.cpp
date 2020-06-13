#include "pch.h"
#include "SoundManager.h"

SoundManager* SoundManager::GetInstance()
{
	static SoundManager* instance;
	if (instance == nullptr)
	{
		instance = new SoundManager();
	}
	return instance;
}

SoundManager::SoundManager()
	: m_pCurrentlyPlayingStream{nullptr}
	, m_SoundEffects{}
	, m_SoundStreams{}
	, m_EffectVolume{50}
	, m_StreamVolume{50}
{
}
SoundManager::~SoundManager()
{
	for (std::unordered_map<std::string, SoundEffect*>::iterator itr{ m_SoundEffects.begin() }; itr != m_SoundEffects.end(); itr++)
	{
		delete itr->second;
	}
	m_SoundEffects.clear();

	for (std::unordered_map<std::string, SoundStream*>::iterator itr{ m_SoundStreams.begin() }; itr != m_SoundStreams.end(); itr++)
	{
		delete itr->second;
	}
	m_SoundStreams.clear();
}

SoundEffect* SoundManager::GetSoundEffect(const std::string& soundFile)
{
	auto pair{ m_SoundEffects.find(soundFile) };

	if (pair != m_SoundEffects.end())
	{
		return pair->second;
	}
	else
	{
		SoundEffect* newEffect{ new SoundEffect(soundFile) };

		if (newEffect->IsLoaded())
		{
			m_SoundEffects[soundFile] = newEffect;
			return m_SoundEffects[soundFile];
		}
		else
		{
			delete newEffect;
		}
	}
	return nullptr;
}
SoundStream* SoundManager::GetSoundStream(const std::string& soundFile)
{
	auto pair{ m_SoundStreams.find(soundFile) };

	if (pair != m_SoundStreams.end())
	{
		return pair->second;
	}
	else
	{
		SoundStream* newStream{ new SoundStream(soundFile) };

		if (newStream->IsLoaded())
		{
			m_SoundStreams[soundFile] = newStream;
			return m_SoundStreams[soundFile];
		}
		else
		{
			delete newStream;
		}
	}
	return nullptr;
}

void SoundManager::PlaySoundEffect(SoundEffect* effect)
{
	if (effect == nullptr)
	{
		return;
	}
	effect->SetVolume(m_EffectVolume);
	effect->Play(0);
}
void SoundManager::PlaySoundStream(SoundStream* stream)
{
	if (m_pCurrentlyPlayingStream != nullptr)
	{
		m_pCurrentlyPlayingStream->Stop();
	}

	if (stream == nullptr)
	{
		return;
	}

	stream->SetVolume(m_StreamVolume);
	stream->Play(true);
	m_pCurrentlyPlayingStream = stream;
}

int SoundManager::GetEffectsVolume() const
{
	return m_EffectVolume;
}
void SoundManager::SetEffectsVolume(int volume)
{
	m_EffectVolume = volume;
}

int SoundManager::GetStreamVolume() const
{
	return m_StreamVolume;
}
void SoundManager::SetStreamVolume(int volume)
{
	m_StreamVolume = volume;
	if (m_pCurrentlyPlayingStream != nullptr)
	{
		m_pCurrentlyPlayingStream->SetVolume(m_StreamVolume);
	}
}