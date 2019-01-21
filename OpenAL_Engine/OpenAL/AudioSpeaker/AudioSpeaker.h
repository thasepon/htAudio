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
		AudioSpeaker(string SoundName, string material);// ���w��
		AudioSpeaker(int id);							// ID�w��
		AudioSpeaker(string SoundName);					// �w��Ȃ�

		~AudioSpeaker();								// ���Еt��

		void SetMaterial(string Name);	// �}�e���A���f�[�^�̐ݒ�
		
		void SetSpeakerAudio(string SoundName, string material);
		void SetSpeakerAudio(int id);
		void SetSpeakerAudio(string SoundName);

		void Play();	// �Đ�����
		void Stop();	// ��~����
		void Pause();	// �ꎞ��~����
		
		bool Update();		// �X�V����
		void StartUpdate();	// �X�V�̊J�n
		void StopUpdate();	// �X�V�̒�~

		bool AddEffects(AudioEffects* effect);		// �G�t�F�N�g�̒ǉ�
		bool RemoveEffects(AudioEffects* effect);	// �G�t�F�N�g�̒ǉ�

		uint16_t GetSpeakerNumb();					// �\�[�X�̔ԍ����擾

	private:
		// === �֐� === //
		bool SetBuffer(ALuint Buf);	// �o�b�t�@�̐ݒ�
		void Init();				// ���ʏ���������
		
		// === �ϐ� === //
		bool Successinit = false;	// �����������t���O
		bool UpdateFlag = false;	// �X�V�t���O

		AudioResources AudioSource;	// �I�[�f�B�I���
		string UseMaterialAtt;		// �Ώۃ}�e���A���̏��
		array<uint16_t,2> Buffers;	// �o�b�t�@�̐ݒ�
		uint16_t Source;					// Source�̐ݒ�
		list<AudioEffects*> EffectSlot;	// �G�t�F�N�g�X���b�g
		ALfloat Volume;					// �{�����[��
		AudioCommand* BufferCommand;	// �o�b�t�@���̃R�}���h
	};

}