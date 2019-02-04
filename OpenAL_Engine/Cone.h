#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio {

	class Cone : public AudioEffects
	{
	public:
		Cone(ALuint source, std::string elementjsonname);
		~Cone();

		void SetConeOuterGain(float val);
		float GetConeOuterGain();

		void SetConeInnerAngle(float val);
		float GetConeInnerAngle();

		void SetConeOuterAngle(float val);
		float GetConeOuterAngle();

	private:
		ALuint Source;

		CONE_INFO Info;
	};

}