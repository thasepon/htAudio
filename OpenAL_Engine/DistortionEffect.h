#pragma once
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"AudioEffects.h"

namespace htAudio {

	struct DISTORTION_INFO
	{
		double EDGE;
		double GAIN;
		double LOWPASS_CUTOFF;
		double EQCENTER;
		double EQBANDWIDTH;
	};

	class DistortionEffect : public AudioEffects
	{
	public:
		DistortionEffect(ALuint source);
		~DistortionEffect();

		void SetEdge(float val);
		void SetGain(float gain);
		void SetLowpassCutOff(float val);
		void SetEQEnter(float val);
		void SetEQBandWidth(float val);

	private:
		DISTORTION_INFO Info;

		double MaxEdge,MinEdge;
		double MaxGain,MinGain;
		double MaxLowpassCutOff, MinLowpassCutOff;
		double MaxEQCenter, MinEQCenter;
		double MaxEQBandWidth, MainEQBandWidth;

	};

}