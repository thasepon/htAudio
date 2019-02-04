#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio {

	class EQEffect :public AudioEffects
	{
	public:
		EQEffect(ALuint source, std::string elementjsonname);
		~EQEffect();

		void SetLow(float gain,float cutoff);
		void SetMid1(float gain,float center,float width);
		void SetMid2(float gain, float center, float width);
		void SetHigh(float gain, float cutoff);


	private:
		EQ_INFO Info;


	};

}