#include "ReverbEffects.h"

namespace htAudio {

	/// <summary>
	/// �T�v :: ���o�[�u�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="source">�ΏۂƂ���Source</param>
	ReverbEffects::ReverbEffects(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
			if (alGetError() != AL_NO_ERROR)
			{
				return;
			}
		}

		alAuxiliaryEffectSloti(EffectSlot, AL_EFFECTSLOT_EFFECT, Effect);

		alSource3i(source, AL_AUXILIARY_SEND_FILTER, EffectSlot, 0, NULL);



	}

	ReverbEffects::~ReverbEffects()
	{
	}

	void ReverbEffects::SetInfo(REVERB_INFO* info)
	{
		Info = info;
	}

	/// <summary>
	/// �T�v :: ���x���l�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// MAX(1.0) :: LOW(0.0) :: Default(1.0)
	/// </summary>
	/// <param name="density">�ݒ肷�閧�x�̒l</param>
	void ReverbEffects::SetDensity(float density)
	{
		Info->DENSITY = density;
		alEffectf(Effect, AL_REVERB_DENSITY, (ALfloat)Info->DENSITY);
	}

	/// <summary>
	/// �T�v :: �g�U���l
	/// �A�N�Z�X���� :: public
	/// MAX(1.0) :: LOW(0.0) :: Default(1.0)
	/// </summary>
	/// <param name="diffusion">�ݒ肷��g�U���l�̒l</param>
	void ReverbEffects::SetDiffusion(float diffusion)
	{
		Info->DIFFUSION = diffusion;
		alEffectf(Effect, AL_REVERB_DIFFUSION, (ALfloat)Info->DIFFUSION);
	}

	/// <summary>
	/// �T�v		:: Gain���l�Ɋւ���ݒ�
	///	�ڍ�		:: ���ˉ��̃}�X�^�[�{�����[���R���g���[��
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="gain">�S�̉��ʂ̒l</param>
	/// MAX(1.0) :: LOW(0.0) :: Default(0.32)
	/// <param name="gainhf">������̉��ʐݒ�</param>
	/// MAX(1.0) :: LOW(0.0) :: Default(0.89)
	void ReverbEffects::SetGain(float gain, float gainhf)
	{
		Info->GAIN = gain;
		Info->GAINHF = gainhf;
		alEffectf(Effect, AL_REVERB_GAIN, (ALfloat)Info->GAIN);
		alEffectf(Effect, AL_REVERB_GAINHF, (ALfloat)Info->GAINHF);
	}

	/// <summary>
	/// �T�v		:: Decay���l�Ɋւ���ݒ�
	///	�ڍ�		:: �����l�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="time">�������x</param>
	/// MAX(20.0) :: LOW(1.0) :: Default(1.49)
	/// <param name="hfratio">������̌������Ԃ̐ݒ�</param>
	/// MAX(2.0) :: LOW(0.1) :: Default(0.83)
	void ReverbEffects::SetDecay(float time, float hfratio)
	{
		Info->DECAY_TIME = time;
		Info->DECAY_HFRATIO = hfratio;
		alEffectf(Effect,AL_REVERB_DECAY_TIME, (ALfloat)Info->DECAY_TIME);
		alEffectf(Effect,AL_REVERB_DECAY_HFRATIO, (ALfloat)Info->DECAY_HFRATIO);
	}

	/// <summary>
	/// �T�v		:: Reflection���l�Ɋւ���ݒ�
	///	�ڍ�		:: �����l�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="gain">�������}�X�^�{�����[���̒l</param>
	/// MAX(3.16) :: LOW(0.0) :: Default(0.05)
	/// <param name="delay">�������̎���</param>
	/// MAX(0.3) :: LOW(1.0) :: Default(0.007)
	void ReverbEffects::SetReflection(float gain, float delay)
	{
		Info->REFLECTIONS_GAIN = gain;
		Info->REFLECTIONS_DELAY = delay;

		alEffectf(Effect, AL_REVERB_REFLECTIONS_GAIN, (ALfloat)Info->REFLECTIONS_GAIN);
		alEffectf(Effect, AL_REVERB_REFLECTIONS_DELAY, (ALfloat)Info->REFLECTIONS_DELAY);
	}

	/// <summary>
	/// �T�v		:: Late���l�Ɋւ���ݒ�
	///	�ڍ�		:: �c�����l�̐ݒ�
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="gain">�}�X�^�{�����[���̐ݒ�</param>
	/// MAX(10.0) :: LOW(0.0) :: Default(1.26)
	/// <param name="reflection">���˂̋����̐ݒ�</param>
	/// MAX(0.1) :: LOW(0.0) :: Default(0.11)
	void ReverbEffects::SetLate(float gain,float reflection)
	{
		Info->LATE_GAIN = gain;
		Info->LATE_DELAY = reflection;

		alEffectf(Effect, AL_REVERB_LATE_REVERB_GAIN, (ALfloat)Info->LATE_GAIN);
		alEffectf(Effect, AL_REVERB_LATE_REVERB_DELAY, (ALfloat)Info->LATE_DELAY);
	}

	/// <summary>
	/// �T�v		:: RoomRollOff���l�Ɋւ���ݒ�
	///	�ڍ�		:: ���ˌ������@�̈��炵��
	///					�����悭�킩��Ȃ����������Č�����ۂɂ͎g�p����̂�������Ȃ�
	///					�_�C���N�g�p�X�T�E���h�Ƃ������̂��傫���ւ���Ă���݂���
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="val">�����l�̐ݒ�</param>
	/// MAX(10.0) :: LOW(0.0) :: Default(0.0)
	void ReverbEffects::SetRoomRollOff(float val)
	{
		Info->ROOM_ROLL_OFF = val;
		alEffectf(Effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, (ALfloat)Info->ROOM_ROLL_OFF);
	}

	/// <summary>
	/// �T�v		:: AIR���l�Ɋւ���ݒ�
	///	�ڍ�		:: ��C�����o�����߂̐��l�炵��
	///					���x�≷�x�ŕω����鉹�̒����p
	/// �A�N�Z�X���� :: public
	/// </summary>
	/// <param name="gainhf">������̃{�����[��</param>
	/// MAX(1.0) :: LOW(0.892) :: Default(0.994)
	/// <param name="hflimit">������J�b�g�������ōs�����ǂ����̃t���O</param>
	/// AL_FALSE AL_TRUE
	void ReverbEffects::SetAir(float gainhf, int hflimit)
	{
		Info->AIR_GAINHF = gainhf;
		Info->AIR_HFLIMIT = hflimit;

		alEffectf(Effect, AL_REVERB_AIR_ABSORPTION_GAINHF, (ALfloat)Info->AIR_GAINHF);
		alEffecti(Effect, AL_REVERB_DECAY_HFLIMIT, (ALint)Info->AIR_HFLIMIT);
	}

}