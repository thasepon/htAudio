#pragma once
#include"OpenAL/OpenAlCore/OpenALDevice.h"

class AudioEffects
{
public:
	AudioEffects();
	~AudioEffects();

	void Update() {}
	
protected:
	ALuint EffectSlot;		// �G�t�F�N�g�X���b�g
	ALuint Effect;			// �G�t�F�N�g

};

