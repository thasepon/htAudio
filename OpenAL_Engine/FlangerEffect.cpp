#include "FlangerEffect.h"
#include"OpenAL\AudioFormatData\AudioFormatData.h"

namespace htAudio {

	/// <summary>
	/// �T�v :: �t�����W���[�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="source">�ΏۂƂ���Source</param>
	FlangerEffect::FlangerEffect(ALuint source, std::string elementjsonname)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_FLANGER);
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


	FlangerEffect::~FlangerEffect()
	{
	}

	/// <summary>
	/// �T�v :: �ǂ��������`�Ő������邩
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="type">type�̒l</param>
	/// MAX(1) :: LOW(0) :: Default(1)
	void FlangerEffect::SetWaveForm(int type)
	{
		Info.WAVEFORM = type;
		alEffectf(Effect, AL_FLANGER_WAVEFORM, Info.WAVEFORM);
	}

	/// <summary>
	/// �T�v :: �ǂ̈ʒu�ɕ΂�����Ԃŏo����
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="ohase">pahse�̒l</param>
	/// MAX(180) :: LOW(-180) :: Default(0)
	void FlangerEffect::SetPhase(int phase)
	{
		Info.PHASE = phase;
		alEffectf(Effect, AL_FLANGER_PHASE, Info.PHASE);
	}

	/// <summary>
	/// �T�v :: �s�b�`�ϒ��̗�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="rate">rate�̒l</param>
	/// MAX(10.0) :: LOW(0.0) :: Default(0.27)
	void FlangerEffect::SetRate(float rate)
	{
		Info.RATE = rate;
		alEffectf(Effect, AL_FLANGER_RATE, (ALfloat)Info.RATE);
	}

	/// <summary>
	/// �T�v :: �s�b�`�̕ω���
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="depth">depth�̒l</param>
	/// MAX(1.0) :: LOW(0.0) :: Default(1.0)
	void FlangerEffect::SetDepth(float depth)
	{
		Info.DEPTH = depth;
		alEffectf(Effect, AL_FLANGER_DEPTH, (ALfloat)Info.DEPTH);
	}

	/// <summary>
	/// �T�v :: ���s�[�g�񐔂̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="feedback"></param>
	/// MAX(1.0) :: LOW(-1.0) :: Default(-0.5)
	void FlangerEffect::SetFeedback(float feedback)
	{
		Info.FEEDBACK = feedback;
		alEffectf(Effect, AL_FLANGER_FEEDBACK, (ALfloat)Info.FEEDBACK);
	}

	/// <summary>
	/// �T�v :: �x�����Ԃ̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="delay"></param>
	/// MAX(0.004) :: LOW(0.0) :: Default(0.002)
	void FlangerEffect::SetDelay(float delay)
	{
		Info.DELAY = delay;
		alEffectf(Effect, AL_FLANGER_DELAY, (ALfloat)Info.DELAY);
	}

}