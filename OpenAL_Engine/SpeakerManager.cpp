#include "SpeakerManager.h"

namespace htAudio
{

	SpeakerManager::SpeakerManager()
	{
	}

	SpeakerManager::~SpeakerManager()
	{
		AllDeleteSpeaker();
	}

	void SpeakerManager::AddSpeaker(AudioSpeaker* speakerptr)
	{
		SpeakerList.push_back(speakerptr);
	}

	void SpeakerManager::SpeakerUpdate()
	{
		if (SpeakerList.empty())
			return;

		for (auto itr : SpeakerList)
		{
			itr->Update();
		}
	}

	void SpeakerManager::RemoveSpeaker(AudioSpeaker* speakerptr)
	{
		if (SpeakerList.empty())
			return;

		for (auto itr = SpeakerList.begin();itr == SpeakerList.end();itr++)
		{
			if (*itr == speakerptr)
			{
				SpeakerList.erase(itr);
				delete speakerptr;
				speakerptr = nullptr;
				break;
			}
		}
	}

	void SpeakerManager::AllDeleteSpeaker()
	{
		if (SpeakerList.empty())
			return;

		for (auto itr = SpeakerList.begin(); itr == SpeakerList.end(); itr++)
		{
			SpeakerList.erase(itr);
			delete *itr;
			*itr = nullptr;
		}

		SpeakerList.clear();
	}

	void SpeakerManager::ControlVolume(VOLUMETYPE type, double value)
	{
		if (SpeakerList.empty())
			return;

		VolumeArray[type] = value;

		for (auto itr : SpeakerList)
		{
			if (itr->GetVolumeType() == type)
			{
				itr->SetVolume(VolumeArray[type]);
			}
		}
	}

}