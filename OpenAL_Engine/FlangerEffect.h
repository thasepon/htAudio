#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio {

	

	class FlangerEffect : public AudioEffects
	{
	public:
		FlangerEffect(ALuint source, std::string elementjsonname);
		~FlangerEffect();

		void SetWaveForm(int type);
		void SetPhase(int phase);
		void SetRate(float rate);
		void SetDepth(float depth);
		void SetFeedback(float feedback);
		void SetDelay(float delay);

	private:
		FLANGER_INFO Info;


	};

}