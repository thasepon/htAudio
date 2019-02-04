#include "WahEffect.h"
#include"OpenAL\AudioFormatData\AudioFormatData.h"

namespace htAudio {

	/// <summary>
	/// �T�v :: Wah�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="source">�ΏۂƂ���Source</param>
	WahEffect::WahEffect(ALuint source, std::string elementjsonname)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
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


	WahEffect::~WahEffect()
	{

	}

	/// <summary>
	/// �T�v :: �ŏ�����ő�ւ̃X�C�[�v�^�C��
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="time">�X�C�[�v�Ɏg�p���鎞��</param>
	/// MAX(1.0) :: LOW(0.0001) :: Default(0.06)
	void WahEffect::SetAttackTime(float time)
	{
		Info.ATTACK_TIME = time;
		alEffectf(Effect, AL_AUTOWAH_ATTACK_TIME, (ALfloat)Info.ATTACK_TIME);
	}

	/// <summary>
	/// �T�v :: �ő傩��x�[�X�ւ̃X�C�[�v�^�C��
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="time">�X�C�[�v�Ɏg�p���鎞��</param>
	/// MAX(1.0) :: LOW(0.0001) :: Default(0.06)
	void WahEffect::SetReleaseTime(float time)
	{
		Info.RELEASE_TIME = time;
		alEffectf(Effect, AL_AUTOWAH_RELEASE_TIME, (ALfloat)Info.RELEASE_TIME);
	}

	/// <summary>
	/// �T�v :: �ǂ̎��g���т��s�[�N�ɐݒ肷�邩
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="time">�s�[�N�̐��l</param>
	/// MAX(1000.0) :: LOW(2.0) :: Default(1000.0)
	void WahEffect::SetResonance(float val)
	{
		Info.RELEASE_TIME = val;
		alEffectf(Effect, AL_AUTOWAH_RELEASE_TIME, (ALfloat)Info.RELEASE_TIME);
	}

	/// <summary>
	/// �T�v :: band-pass filter���̎g�p���x��
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="gain">gain�̐ݒ�</param>
	/// MAX(31621.0) :: LOW(0.00003) :: Default(11.22)
	void WahEffect::SetPeakGain(float gain)
	{
		Info.PEAK_GAIN = gain;
		alEffectf(Effect, AL_AUTOWAH_PEAK_GAIN,(ALfloat)Info.PEAK_GAIN);
	}

}