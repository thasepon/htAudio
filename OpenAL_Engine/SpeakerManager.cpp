#include "SpeakerManager.h"

namespace htAudio
{

	SpeakerManager::SpeakerManager()
	{
	}


	SpeakerManager::~SpeakerManager()
	{
	}

	void SpeakerManager::AddSpeaker(AudioSpeaker* speakerptr)
	{
		SpeakerList.push_back(speakerptr);
	}

	void SpeakerManager::SpeakerUpdate()
	{
		for (auto itr : SpeakerList)
		{
			itr->Update();
		}

	}

	void SpeakerManager::RemoveSpeaker(AudioSpeaker* speakerptr)
	{
		for (auto itr : SpeakerList)
		{
			if (itr == speakerptr)
			{
				delete itr;
				itr = nullptr;
				SpeakerList.remove(itr);
				break;
			}
		}
	}

	void SpeakerManager::AllDeleteSpeaker()
	{
		for (auto itr : SpeakerList)
		{
			delete itr;
			itr = nullptr;
			SpeakerList.remove(itr);
		}
	}

	void SpeakerManager::ControlVolume(VOLUMETYPE type, double value)
	{
		VolumeArray[type] = value;

		for (auto itr : SpeakerList)
		{
			if (itr->GetVolumeType == type)
			{
				itr->SetVolume(VolumeArray[type]);
			}
		}
	}

}