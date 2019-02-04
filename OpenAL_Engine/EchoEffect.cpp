#include "EchoEffect.h"
#include"OpenAL\AudioFormatData\AudioFormatData.h"

namespace htAudio {

	/// <summary>
	/// �T�v :: �G�R�[�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="source">�ΏۂƂ���Source</param>
	EchoEffect::EchoEffect(ALuint source, std::string elementjsonname)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_ECHO);
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

	EchoEffect::~EchoEffect()
	{
	}

	/// <summary>
	/// �T�v :: �f�B���C�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="delay">delay�̒l�̐ݒ�</param>
	/// MAX(0.207) :: MIN(0.0) :: Default(0.1)
	void EchoEffect::SetDelay(float delay)
	{
		Info.DELAY = delay;
		alEffectf(Effect, AL_ECHO_DELAY, (ALfloat)Info.DELAY);
	}

	/// <summary>
	/// �T�v :: LR�̃f�B���C�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="lrdelay">���ڂ̒x���̐���</param>
	/// MAX(0.404) :: MIN(0.0) :: Default(0.1)
	void EchoEffect::SetLRDelay(float lrdelay)
	{
		Info.LRDELAY = lrdelay;
		alEffectf(Effect, AL_ECHO_LRDELAY, (ALfloat)Info.LRDELAY);
	}

	/// <summary>
	/// �T�v :: �G�R�[�̋���(�Ӗ�)
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="damping">damping�̐��l</param>
	/// MAX(0.99) :: MIN(0.0) :: Default(0.5)
	void EchoEffect::SetDamping(float damping)
	{
		Info.DAMPING = damping;
		alEffectf(Effect, AL_ECHO_DAMPING, (ALfloat)Info.DAMPING);
	}

	/// <summary>
	/// �T�v :: sample�̒���
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="feedback">feedback�̋���</param>
	/// MAX(1.0) :: MIN(0.0) :: Default(0.5)
	void EchoEffect::SetFeedBack(float feedback)
	{
		Info.FEEDBACK = feedback;
		alEffectf(Effect, AL_ECHO_FEEDBACK, (ALfloat)Info.FEEDBACK);
	}

	/// <summary>
	/// �T�v :: �p���j���O�̈ʒu
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="spread">�p���j���O�̈ʒu</param>
	/// MAX(1.0) :: MIN(-1.0) :: Default(-1.0)
	void EchoEffect::SetSpRead(float spread)
	{
		Info.SPREAD = spread;
		alEffectf(Effect, AL_ECHO_SPREAD, (ALfloat)Info.SPREAD);
	}

}