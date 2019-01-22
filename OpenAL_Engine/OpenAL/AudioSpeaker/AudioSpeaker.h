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
		AudioSpeaker();
		AudioSpeaker(string SoundName);	// ���w��
		AudioSpeaker(int id);			// ID�w��

		~AudioSpeaker();								// ���Еt��

		void SetMaterial(string Name);	// �}�e���A���f�[�^�̐ݒ�

		void SetAudioSorce(string SoundName);	// �I�[�f�B�I�f�[�^�̐ݒ� �t�@�C����
		void SetAudioSorce(int id);				// �I�[�f�B�I�f�[�^�̐ݒ� ID

		void Play();	// �Đ�����
		void Stop();	// ��~����
		void Pause();	// �ꎞ��~����
		
		bool Update();		// �X�V����

		bool AddEffects(AudioEffects* effect);		// �G�t�F�N�g�̒ǉ�
		bool RemoveEffects(AudioEffects* effect);	// �G�t�F�N�g�̒ǉ�

		ALuint GetSpeakerNumb();					// �\�[�X�̔ԍ����擾

	private:
		// === �֐� === //
		bool SetBuffer(ALuint Buf);	// �o�b�t�@�̐ݒ�
		void Init();					// ���ʏ���������
		
		void RegistAudioSource(int numb); // �ԍ����w�肵�ă\�[�X���擾
		
		// === �ϐ� === //
		bool Successinit = false;	// �����������t���O
		
		INT16 NowUsedNumb;			// ���ݎg�p���Ă���SoundType�̔ԍ�
		AudioResources AudioSource;	// �I�[�f�B�I���
		string UseMaterialAtt = ""; // �Ώۃ}�e���A���̏��
		array<ALuint,2> Buffers;	// �o�b�t�@�̐ݒ�
		ALuint Source;					// Source�̐ݒ�
		list<AudioEffects*> EffectSlot;	// �G�t�F�N�g�X���b�g
		double Volume;					// �{�����[��
		AudioCommand* BufferCommand;	// �o�b�t�@���̃R�}���h
	};

}