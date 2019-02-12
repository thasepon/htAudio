#include "AudioGroup.h"
#include <utility>
#include <functional>

namespace htAudio {


	AudioGroup::AudioGroup()
	{
		GroupIdCnter = 0;
	}


	AudioGroup::~AudioGroup()
	{
	}

	std::map<std::string, GropuInfo> AudioGroup::GetGropulist()
	{
		if (!AudioGropulist.empty())
		{
			AudioGropulist.clear();
		}

		return AudioGropulist;

	}

	void AudioGroup::CreateGropu(std::string name)
	{
		GroupIdCnter++;

		GropuInfo AudioGroup;
		AudioGroup.GropName = name;
		AudioGroup.GroupId = GroupIdCnter;

		AudioGropulist.insert(std::make_pair(name,AudioGroup) );
	}

	void AudioGroup::DeleteGropu(std::string name)
	{
		if (AudioGropulist.empty())
			return;

		auto itr = AudioGropulist.find(name);
		if (itr != AudioGropulist.end())
		{
			AudioGropulist.erase(itr);
		}

	}

}