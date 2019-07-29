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
		~AudioSpeaker();							// �X�s�[�J�[�̍폜����

		bool SetMaterialName(string Name);			// �}�e���A���f�[�^�̐ݒ�

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
		void DecodeAudioStreamBuffer();		// �w�肵��Audio��񂩂�o�b�t�@���l��
		void InitStreamBuffer();			// �w��Audio��stream�^�C�v�������ꍇ�̏���������
		void ReadHeaderInfo();				// �w�b�_�[���̓ǂݍ���
		bool AddEffects();					// �G�t�F�N�g�̓K���Ɛݒ�
		void UpdateStreamBuffer(void* buf);				// �o�b�t�@�X�V�p�֐�

		// === �\���̐錾 === //
		AudioData SpeakerData;					// Audio�̃f�[�^(�g���܂킵����\��)
		AUDIOFILEFORMAT HeaderFormat;			// �w�b�_�[���
		AudioCue SpeakerCue;					// Json���瓾�����(�P��f�[�^)
		std::vector<SoundType> SoundDatas;		// Json���瓾�����(�����̃f�[�^������܂�)
		AudioBuffer SpeakerBuffer;

		// === �ϐ� === //
		uint16_t NowUsedNumb;					// ���ݎg�p���Ă���SoundType�̔ԍ�
		uint16_t StreamBufSize;					// �o�b�t�@�T�C�Y
		
		std::string UseMaterialAtt;				// ���݂̃}�e���A�����
		
		std::string CueName;					// �w��Cue�̖��O(CueId�����ł���)
		int CueId;								// �w��Cue��Id(CueName�����ł���)

		bool HasGotWaveFormat;					// �t�H�[�}�b�g�擾�ɐ������Ă��邩

		ALuint Source;							// Source�̐ݒ�
		ALuint Buffers[2];						// �o�b�t�@�̐ݒ�

		std::shared_ptr <SetBufCommand> BufferCommand;	// �o�b�t�@�ݒ�p�R�}���h
		std::shared_ptr <AddEffectCommand> EffectCommand;	// �G�t�F�N�g�R�}���h

		std::vector<AudioEffects*> EffectSlot;	// �X�s�[�J�[�K������G�t�F�N�g�X���b�g

	};

}