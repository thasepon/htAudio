#pragma once
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"AudioEffects.h"

namespace htAudio {

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


	};

}