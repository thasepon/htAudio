#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	struct EQ_INFO
	{
		double LOW_GAIN;
		double LOW_CUTOFF;
		double MID1_GAIN;
		double MID1_CENTER;
		double MID1_WIDTH;
		double MID2_GAIN;
		double MID2_CENTER;
		double MID2_WIDTH;
		double HIGH_GAIN;
		double HIGH_CUTOFF;
	};

	class EQEffect :public AudioEffects
	{
	public:
		EQEffect(ALuint source);
		~EQEffect();

		void SetLow(float gain,float cutoff);
		void SetMid1(float gain,float center,float width);
		void SetMid2(float gain, float center, float width);
		void SetHigh(float gain, float cutoff);


	private:
		EQ_INFO Info;

		double MaxLowGain,MinLowGain;
		double MaxLowCutOff,MinLowCutOff;
		double MaxMidGain,MinMidGain;
		double MaxMidCenter,MinMidCenter;
		double MaxMidWidth,MinMidWidth;
		double MaxMid2Gain, MinMid2Gain;
		double MaxMid2Center, MinMid2Center;
		double MaxMid2Width, MinMid2Width;
		double MaxHighGain,MinHighGain;
		double MaxHighCutOff, MinHighCutOff;

	};

}