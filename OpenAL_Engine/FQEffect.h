#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio {

	class FQEffect : public AudioEffects
	{
	public:
		FQEffect(ALuint source, std::string elementjsonname);
		~FQEffect();

		void SetFrequency(float fq);
		void SetLRDirection(int left , int right);

	private:
		FQ_INFO Info;

	};

}