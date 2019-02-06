#pragma once
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"EffectElementPram.h"

namespace htAudio
{
	// ===  �e�G�t�F�N�g�̍\���� === //
	struct I3DAudioInfo
	{
		ALfloat* Position[3];	// Position
		ALfloat* Velocity[3];	// �ړ����x
		ALfloat* Direction[3];	// ����
	};

	struct CHORUS_INFO
	{
		double CorrectionValue;	// 0.0-1.0�̊ԂŎw�肷��
		uint16_t WAVEROTM;
		uint16_t PHASE;
		double RATE;
		double DEPTH;
		double FEEDBACK;
		double DELAY;
		uint16_t MaxWaveRotm, MinWaveRotm;
		uint16_t MaxPhase, MinPhase;
		double MaxRate, MinRate;
		double MaxDepth, MinDepth;
		double MaxFeedback, MinFeedback;
		double MaxDelay, MinDelay;
	}; 
	
	struct DISTORTION_INFO
	{
		double CorrectionValue;
		double EDGE;
		double GAIN;
		double LOWPASS_CUTOFF;
		double EQCENTER;
		double EQBANDWIDTH;
		double MaxEdge, MinEdge;
		double MaxGain, MinGain;
		double MaxLowpassCutOff, MinLowpassCutOff;
		double MaxEQCenter, MinEQCenter;
		double MaxEQBandWidth, MinEQBandWidth;
	};

	struct ECHO_INFO
	{
		double CorrectionValue;
		double DELAY;
		double LRDELAY;
		double DAMPING;
		double FEEDBACK;
		double SPREAD;
		double MaxDelay, MinDelay;
		double MaxLRDelay, MinLRDelay;
		double MaxDamping, MinDamping;
		double MaxFeedBack, MinFeedBack;
		double MaxSPRead, MinSPRead;
	};

	struct EQ_INFO
	{
		double CorrectionValue;
		double LOW_GAIN;
		double LOW_CUTOFF;
		double MID1_GAIN;
		double MID1_CENTER;
		double MID1_WIDTH;
		double MID2_GAIN;
		double MID2_CENTER;
		double MID2_WIDTH;
		double HIGH_GAIN;
		double HIGH_CUTOFF;
		double MaxLowGain, MinLowGain;
		double MaxLowCutOff, MinLowCutOff;
		double MaxMidGain, MinMidGain;
		double MaxMidCenter, MinMidCenter;
		double MaxMidWidth, MinMidWidth;
		double MaxMid2Gain, MinMid2Gain;
		double MaxMid2Center, MinMid2Center;
		double MaxMid2Width, MinMid2Width;
		double MaxHighGain, MinHighGain;
		double MaxHighCutOff, MinHighCutOff;
	};

	struct FLANGER_INFO
	{
		double CorrectionValue;
		uint16_t WAVEFORM;
		uint16_t PHASE;
		double RATE;
		double DEPTH;
		double FEEDBACK;
		double DELAY;
		uint16_t MaxWaveForm, MinWaveForm;
		uint16_t MaxPhase, MinPhase;
		double MaxRate, MinRate;
		double MaxDepth, MinDepth;
		double MaxFeedback, MinFeedback;
		double MaxDelay, MinDelay;
	};

	struct FQ_INFO
	{
		double CorrectionValue;
		double FREQUENCY;
		uint16_t LEFT_DIRECTION;
		uint16_t RIGHT_DIRECTION;
		double MaxFrequency, MinFrequency;
		uint16_t MaxLeftDirection, MinLeftDirection;
		uint16_t MaxRightDirection, MinRightDirection;
	};

	struct PITCH_INFO
	{
		double CorrectionValue;
		uint16_t COARSE_TUNE;
		uint16_t FINE_TUNE;
		uint16_t MaxCoarseTune, MinCoarseTune;
		uint16_t MaxFineTune, MinFineTune;
	};

	struct REVERB_INFO
	{
		double CorrectionValue;
		double DENSITY;
		double DIFFUSION;
		double GAIN;
		double GAINHF;
		double DECAY_TIME;
		double DECAY_HFRATIO;
		double REFLECTIONS_GAIN;
		double REFLECTIONS_DELAY;
		double LATE_GAIN;
		double LATE_DELAY;
		double ROOM_ROLL_OFF;
		double AIR_GAINHF;
		bool AIR_HFLIMIT;
		double MaxDensity, MinDensity;
		double MaxDiffusion, MinDiffusion;
		double MaxGain, MinGain;
		double MaxGainHF, MinGainHF;
		double MaxDecayTime, MinDecayTime;
		double MaxDecayHFRatio, MinDecayHFRatio;
		double MaxReflectionsGain, MinReflectionsGain;
		double MaxReflectionsDelay, MinReflectionsDelay;
		double MaxLateGain, MinLateGain;
		double MaxLateDelay, MinLateDelay;
		double MaxRoomRollOff, MinRoomRollOff;
		double MaxAirGainHF, MinAirGainHF;
	};

	struct WAH_INFO
	{
		double CorrectionValue;
		double ATTACK_TIME;
		double RELEASE_TIME;
		double RESONANCE;
		double PEAK_GAIN;
		double MaxAttackTime, MinAttackTime;
		double MaxRleaseTime, MinRleaseTime;
		double MaxResonace, MinResonace;
		double MaxPeakGain, MinPeakGain;
	};

	struct CONE_INFO
	{
		double CorrectionValue;
		double ConeOuterGain;	// �R�[���̊O���Q�C�����l
		double InnerAngle;		// �����̊p�x
		double OuterAngle;		// �O���̊p�x
	};

	// === �e��G�t�F�N�g�̃x�[�X�N���X === //
	class AudioEffects
	{
	public:
		AudioEffects();
		~AudioEffects();

		void Update() {}

		void SetEffectParametr(EffectElementPram* pram) { EffectPram = pram; }
		std::string GetEffectPramName() { return EffectPramName; }


	protected:
		ALuint EffectSlot;		// �G�t�F�N�g�X���b�g
		ALuint Effect;			// �G�t�F�N�g
		EffectElementPram* EffectPram;	// �G�t�F�N�g�̐��l��ύX���邽�߂̃N���X
		std::string EffectPramName;		// �G�t�F�N�g�̑Ώۂ��擾


	};

}