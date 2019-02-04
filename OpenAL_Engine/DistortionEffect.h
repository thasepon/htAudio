#pragma once
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"AudioEffects.h"
#include<string>

namespace htAudio {

	class DistortionEffect : public AudioEffects
	{
	public:
		DistortionEffect(ALuint source, std::string elementjsonname);
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