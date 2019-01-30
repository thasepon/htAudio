#include "AudioFormatData.h"
#include <codecvt>

namespace htAudio {

	using namespace pugi;

	AudioFormatData::AudioFormatData()
	{
	}


	AudioFormatData::~AudioFormatData()
	{

	}

	std::vector<SoundType> AudioFormatData::GetAudioFormatData(std::string filepath, std::string Soundname)
	{
		
		std::vector<SoundType> Formats;
		SoundType Format;
		


		Format.CreateFlag = true;
		return Formats;
	}


	std::vector<SoundType> AudioFormatData::GetAudioFormatData(std::string filepath, int id)
	{
		std::vector<SoundType> Formats;
		SoundType Format;
		


		Format.CreateFlag = true;
		return Formats;

	}

	bool AudioFormatData::ReadListenerState(ConeState& state, std::string filepath)
	{
		


		return true;
	}

}