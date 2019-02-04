#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio {


	class WahEffect :public AudioEffects
	{
	public:
		WahEffect(ALuint source, std::string elementjsonname);
		~WahEffect();

		void SetAttackTime(float time);
		void SetReleaseTime(float time);
		void SetResonance(float val);
		void SetPeakGain(float gain);

	private:
		WAH_INFO Info;


	};

}