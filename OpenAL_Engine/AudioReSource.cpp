#include "AudioReSource.h"

namespace htAudio
{

	AudioReSource::AudioReSource()
	{
		AudioresourceMap.clear();
	}

	AudioReSource::~AudioReSource()
	{

	}

	void AudioReSource::PreLoad(std::string)
	{
		AudioResources* resource;



	}

	void AudioReSource::PreLoad(int Id)
	{

	}

	void AudioReSource::StreamLoad(std::string)
	{

	}

	void AudioReSource::StreamLoad(int Id)
	{

	}

	/// <summary>
	/// 現在使用している
	/// </summary>
	void AudioReSource::ReleaseResource()
	{

		for (auto x : AudioresourceMap)
		{

		}

	}

}