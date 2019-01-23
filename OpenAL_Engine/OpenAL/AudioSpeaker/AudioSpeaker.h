#pragma once

#include"../../AudioData.h"
#include"../../AudioReSource.h"
#include"../../AudioEffects.h"

#include"../../PlayCommand.h"
#include"../../StopCommand.h"
#include"../../PauseCommand.h"

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
		AudioSpeaker(string SoundName);				// ���O�w��Ń\�[�X�𐶐�
		AudioSpeaker(int id);						// ID�w��Ń\�[�X�𐶐�
		~AudioSpeaker();							// �X�s�[�J�[�̍폜����

		void SetMaterial(string Name);				// �}�e���A���f�[�^�̐ݒ�
		void SetAudioSorce(string SoundName);		// �I�[�f�B�I�f�[�^�̐ݒ� �t�@�C����
		void SetAudioSorce(int id);					// �I�[�f�B�I�f�[�^�̐ݒ� ID
		
		bool Update();								// �X�V����
		bool AddEffects(AudioEffects* effect);		// �G�t�F�N�g�̒ǉ�
		bool RemoveEffects(AudioEffects* effect);	// �G�t�F�N�g�̍폜

		ALuint GetSpeakerNumb();					// �\�[�X�̔ԍ����擾

	private:
		// === �֐� === //
		void Init();						// ���ʏ���������
		void RegistAudioSource(int numb);	// �w�肵��Audio��񂩂�o�b�t�@���l��
		
		void Play();						// �Đ����� [�O���ďo���̗\��͌��ݖ���]
		void Stop();						// ��~���� [�O���ďo���̗\��͌��ݖ���]
		void Pause();						// �ꎞ��~���� [�O���ďo���̗\��͌��ݖ���]

		
		// === �ϐ� === //
		bool Successinit = false;			// �����������t���O
		uint16_t NowUsedNumb;				// ���ݎg�p���Ă���SoundType�̔ԍ�
		AudioResources AudioSource;			// �I�[�f�B�I���
		string UseMaterialAtt = "";			// �Ώۃ}�e���A���̏��
		array<ALuint,2> Buffers;			// �o�b�t�@�̐ݒ�
		ALuint Source;						// Source�̐ݒ�
		list<AudioEffects*> EffectSlot;		// �G�t�F�N�g�X���b�g

		AudioCommand* BufferCommand;		// �o�b�t�@�ݒ�R�}���h


	};

}