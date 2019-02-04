#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio {

	class EchoEffect : public AudioEffects
	{
	public:
		EchoEffect(ALuint source, std::string elementjsonname);
		~EchoEffect();

		void SetDelay(float delay);
		void SetLRDelay(float lrdelay);
		void SetDamping(float damping);
		void SetFeedBack(float feedback);
		void SetSpRead(float spread);

	private:
		ECHO_INFO Info;
	};

}