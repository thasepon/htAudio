#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio
{
	class PitchEffect : public AudioEffects
	{
	public:
		PitchEffect(ALuint source, std::string elementjsonname);
		~PitchEffect();

		void SetCoarse(int coarse);
		void SetFine(int fine);

	private:

		PITCH_INFO Info;
	};

}