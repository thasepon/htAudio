#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	class FQEffect : public AudioEffects
	{
	public:
		FQEffect(ALuint source);
		~FQEffect();

		void SetFrequency(float fq);
		void SetLRDirection(int left , int right);

	private:
		FQ_INFO Info;

	};

}