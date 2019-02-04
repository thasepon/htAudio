#include "FQEffect.h"
#include"OpenAL\AudioFormatData\AudioFormatData.h"

namespace htAudio {

	/// <summary>
	/// �T�v :: ���o�[�u�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="source">�ΏۂƂ���Source</param>
	FQEffect::FQEffect(ALuint source, std::string elementjsonname)
	{
		LPALGENEFFECTS algeneffect = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");

		alGenAuxiliaryEffectSlots(1, &EffectSlot);

		if (alGetError() != AL_NO_ERROR)
			return;

		algeneffect(1, &Effect);

		if (alGetError() != AL_NO_ERROR)
			return;

		if (alIsEffect(Effect))
		{
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
			if (alGetError() != AL_NO_ERROR)
			{
				return;
			}
		}

		alAuxiliaryEffectSloti(EffectSlot, AL_EFFECTSLOT_EFFECT, Effect);

		if (alGetError() == AL_NO_ERROR)
		{
			alSource3i(source, AL_AUXILIARY_SEND_FILTER, EffectSlot, 0, NULL);
		}
		AudioFormatData::LoadEffectData(Info, elementjsonname);
	}


	FQEffect::~FQEffect()
	{

	}

	/// <summary>
	/// �T�v :: �ω��ʂ̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="fq">fq�̕ω��̒l</param>
	/// MAX(24000.0) :: LOW(0.0) :: Default(0.0)
	void FQEffect::SetFrequency(float fq)
	{
		Info.FREQUENCY = fq;
		alEffectf(Effect, AL_FREQUENCY_SHIFTER_FREQUENCY, (ALfloat)Info.FREQUENCY);
	}

	/// <summary>
	/// �T�v :: �����M���̉��Z�̐ݒ�
	/// </summary>
	/// <param name="left">left�̐ݒ�</param>
	/// <param name="right">right�̐ݒ�</param>
	/// down(0) :: Up(1) :: Off(2)
	void FQEffect::SetLRDirection(int left, int right)
	{
		Info.LEFT_DIRECTION = left;
		Info.RIGHT_DIRECTION = right;

		alEffectf(Effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION , Info.LEFT_DIRECTION);
		alEffectf(Effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION , Info.RIGHT_DIRECTION);
	}


}