#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {


	class WahEffect :public AudioEffects
	{
	public:
		WahEffect(ALuint source);
		~WahEffect();

		void SetAttackTime(float time);
		void SetReleaseTime(float time);
		void SetResonance(float val);
		void SetPeakGain(float gain);

	private:
		WAH_INFO Info;


	};

}