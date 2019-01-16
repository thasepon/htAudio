#include "PitchEffect.h"

namespace htAudio
{
	/// <summary>
	/// �T�v :: �s�b�`�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="source">�ΏۂƂ���Source</param>
	PitchEffect::PitchEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
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
	}


	PitchEffect::~PitchEffect()
	{
	}

	/// <summary>
	/// �T�v :: �s�b�`�V�t�g�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="coarse">���炷���K��</param>
	/// MAX(12.0) :: LOW(-12.0) :: Default(12.0)
	void PitchEffect::SetCoarse(int coarse)
	{
		Info.COARSE_TUNE = coarse;
		alEffectf(Effect, AL_PITCH_SHIFTER_COARSE_TUNE, Info.COARSE_TUNE);
	}

	/// <summary>
	/// �T�v :: �s�b�`�V�t�g(����)�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="fine"></param>
	/// MAX(50.0) :: LOW(-50.0) :: Default(0.0)
	void PitchEffect::SetFine(int fine)
	{
		Info.FINE_TUNE = fine;
		alEffectf(Effect, AL_PITCH_SHIFTER_FINE_TUNE, Info.FINE_TUNE);
	}
}