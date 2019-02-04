#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include<string>

namespace htAudio
{
	

	class ReverbEffects : public AudioEffects
	{
	public:
		ReverbEffects(ALuint source,std::string elementjsonname);
		~ReverbEffects();

		void SetInfo(REVERB_INFO Info);

		void SetDensity(float density);
		void SetDiffusion(float diffusion);
		void SetGain(float gain,float gainhf);
		void SetDecay(float time , float hfratio);
		void SetReflection(float gain ,float delay);
		void SetLate(float gain, float reflection);
		void SetRoomRollOff(float val);
		void SetAir(float gainhf, int hflimit);

	private:
		REVERB_INFO Info;		// ÉäÉoÅ[ÉuèÓïÒ

	};

}