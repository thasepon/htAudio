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
	/// åªç›égópÇµÇƒÇ¢ÇÈ
	/// </summary>
	void AudioReSource::ReleaseResource()
	{

		for (auto x : AudioresourceMap)
		{

		}

	}

}