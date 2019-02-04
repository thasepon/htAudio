#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio
{
	class ChorusEffect : public AudioEffects
	{
	public:
		ChorusEffect(ALuint source, std::string elementjsonname);
		~ChorusEffect();
	
		void SetWaveForm(int form);
		void SetPhase(int value);
		void SetRate(float rate);
		void SetDepth(float value);
		void SetFeedBack(float value);
		void SetDelay(float value);

	private:
		CHORUS_INFO Info;

	};
}