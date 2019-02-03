#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	
	class I3DAudio : public AudioEffects
	{
	public:
		I3DAudio(ALuint source);
		I3DAudio(ALuint source, I3DAudioInfo* info);
		~I3DAudio();

		void SetPosition(float* x, float* y, float* z);
		void SetPosition(float* pos[3]);

		void SetVelocity(float* x, float* y, float* z);
		void SetVelocity(float* vec[3]);

		void SetDirection(float* x, float* y, float* z);
		void SetDirection(float* dir[3]);

		void Update();

	private:

		ALuint Source;

		// �󂯓n���ő��v�ȏ��
		float Gain;
		
		// �|�C���^�ŗ~�������
		I3DAudioInfo* Info;

	};

}