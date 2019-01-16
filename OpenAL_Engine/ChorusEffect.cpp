#include "ChorusEffect.h"


namespace htAudio
{
	/// <summary>
	/// �T�v :: �R�[���X�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="source">�ΏۂƂ���Source</param>
	ChorusEffect::ChorusEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_CHORUS);
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


	ChorusEffect::~ChorusEffect()
	{
	}

	/// <summary>
	/// �T�v :: �ǂ��������`�Ő������邩
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="form">�t�H�[�}�b�g�̌`��</param>
	/// 1(sin) 1(trinangle)
	void ChorusEffect::SetWaveForm(int form)
	{
		Info.WAVEROTM = form;
		alEffectf(Effect, AL_CHORUS_WAVEFORM, Info.WAVEROTM);
	}

	/// <summary>
	/// �T�v :: �ʑ����̐���
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="value">�ʒu�̒l</param>
	/// MAX(180) :: MIN(-180) :: Default :: 90
	void ChorusEffect::SetPhase(int value)
	{
		Info.PHASE = value;
		alEffectf(Effect, AL_CHORUS_PHASE, Info.PHASE);
	}

	/// <summary>
	/// �T�v :: �x�����Ԃ̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="rate">�x�����Ԃ̒l</param>
	/// MAX(10.0) :: MIN(0.0) :: Default(1.1)
	void ChorusEffect::SetRate(float rate)
	{
		Info.RATE = rate;
		alEffectf(Effect, AL_CHORUS_RATE, (ALfloat)Info.RATE);
	}

	/// <summary>
	/// �T�v :: �[�x�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="value">�[�x�l</param>
	/// MAX(1.0) :: MIN(0.0) :: Default(0.1)
	void ChorusEffect::SetDepth(float value)
	{
		Info.DEPTH = value;
		alEffectf(Effect, AL_CHORUS_DEPTH, (ALfloat)Info.DEPTH);
	}

	/// <summary>
	/// �T�v :: �t�B�[�h�o�b�N����鐔�l�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="value">�t�B�[�h�o�b�N�̒l</param>
	/// MAX(1.0) :: MIX(-1.0) :: Default(0.25)
	void ChorusEffect::SetFeedBack(float value)
	{
		Info.FEEDBACK = value;
		alEffectf(Effect, AL_CHORUS_FEEDBACK, (ALfloat)Info.FEEDBACK);
	}

	/// <summary>
	/// �T�v :: �f�B���C���l�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="value">�f�B���C���l�̐ݒ�</param>
	/// MAX(0.016) :: MIN(0.0) :: Default(0.016)
	void ChorusEffect::SetDelay(float value)
	{
		Info.DELAY = value;
		alEffectf(Effect, AL_CHORUS_DELAY, (ALfloat)Info.DELAY);
	}

}