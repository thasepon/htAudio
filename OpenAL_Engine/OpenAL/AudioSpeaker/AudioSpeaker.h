#pragma once

#include"../../AudioData.h"
#include"../../AudioReSource.h"
#include"../../AudioEffects.h"

#include"../../SetBufCommand.h"
#include"../../AddEffectCommand.h"

#include<string>
#include<memory>
#include<array>
#include<functional>
#include<future>

#include<AL/efx.h>
#include<AL/efx-creative.h>

namespace htAudio
{
	using namespace std;

	/// <summary>
	/// �T�E���h�̍Đ��p�N���X
	/// �T�E���h�Đ��̑����N���X
	/// </summary>
	class AudioSpeaker
	{
	public:
		AudioSpeaker();								// �X�s�[�J�[�݂̂𐶐�
		AudioSpeaker(string filename);				// ���O�w��Ń\�[�X�𐶐�
		AudioSpeaker(int id);						// ID�w��Ń\�[�X�𐶐�
		~AudioSpeaker();							// �X�s�[�J�[�̍폜����

		void SetMaterial(string Name);				// �}�e���A���f�[�^�̐ݒ�
		void SetAudioSorce(string filename);		// �I�[�f�B�I�f�[�^�̐ݒ� �t�@�C����
		void SetAudioSorce(int id);					// �I�[�f�B�I�f�[�^�̐ݒ� ID
		void SetVolume(double volume);				// �{�����[���̐ݒ�
		
		bool Update();								// �X�V����
		
		ALuint GetSpeakerNumb();					// �\�[�X�̔ԍ����擾
		VOLUMETYPE GetVolumeType();					// Cue�̃{�����[���^�C�v���擾
		
	private:
		// === �֐� === //
		void Init();						// ���ʏ���������
		void DecodeAudioHeader();			// �w�肵��Audio��񂩂�w�b�_�[�����擾
		void DecodeAudioBuffer();			// �w�肵��Audio��񂩂�o�b�t�@���l��
		void ReadHeaderInfo();				// �w�b�_�[���̓ǂݍ���
		bool AddEffects();					// �G�t�F�N�g�̓K���Ɛݒ�

		void Play();						// �Đ����� ��[�O���ďo���̗\��͌��ݖ���:Not_Used]
		void Stop();						// ��~���� ��[�O���ďo���̗\��͌��ݖ���:Not_Used]
		void Pause();						// �ꎞ��~���� ��[�O���ďo���̗\��͌��ݖ���:Not_Used]

		// === �ϐ� === //
		bool Successinit = false;				// �����������t���O
		uint16_t NowUsedNumb;					// ���ݎg�p���Ă���SoundType�̔ԍ�
		
		AudioData SpeakerData;					// Audio�̃f�[�^(�g���܂킵����\��)
		AUDIOFILEFORMAT HeaderFormat;			// �w�b�_�[���
		std::vector<SoundType> SoundDatas;		// XML���瓾�����(�����̃f�[�^������܂�)
		AudioCue SpeakerCue;					// XML���瓾�����(�P��f�[�^)

		std::vector<char> PrimaryMixed;			// �o�b�t�@�ۑ�[1]
		std::vector<char> SecondMixed;			// �o�b�t�@�ۑ�[2](Preload�̏ꍇ�͖��g�p)
		std::string UseMaterialAtt;				// ���݂̃}�e���A�����

		ALuint Source;							// Source�̐ݒ�
		ALuint UpdateBufQue;					// �C���L���[�f�L���[����o�b�t�@�̑I��
		array<ALuint,2> Buffers;				// �o�b�t�@�̐ݒ�

		unique_ptr<SetBufCommand> BufferCommand;	// �o�b�t�@�ݒ�p�R�}���h
		unique_ptr<AddEffectCommand> EffectCommand;	// �G�t�F�N�g�R�}���h

		std::vector<AudioEffects*> EffectSlot;	// �X�s�[�J�[�K������G�t�F�N�g�X���b�g
	};

}