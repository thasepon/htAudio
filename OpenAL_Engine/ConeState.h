#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	class ConeState : public AudioEffects
	{
	public:
		ConeState(ALuint source);
		~ConeState();

		void SetConeOuterGain(float val);
		float GetConeOuterGain();

		void SetConeInnerAngle(float val);
		float GetConeInnerAngle();

		void SetConeOuterAngle(float val);
		float GetConeOuterAngle();

	private:
		ALuint Source;

		ALfloat ConeOuterGain;	// �R�[���̊O���Q�C�����l
		ALfloat InnerAngle;		// �����̊p�x
		ALfloat OuterAngle;		// �O���̊p�x

	};

}