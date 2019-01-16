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
		// ���w��
		AudioSpeaker(string filepath, string SoundName, string material);
		// ID�w��
		AudioSpeaker(string filepath, int id);
		//�w��Ȃ�
		AudioSpeaker(string filepath, string SoundName);
		
		~AudioSpeaker();// �f�X�g

		void StopUpdate();

		bool AddEffects(AudioEffects* effect);

		ALuint GetSpeakerNumb() { return Source; }
		bool Update();									// �X�V

	private:
		bool SetBuffer(ALuint Buf);						// �o�b�t�@�̐ݒ�
		void Init();									// ���ʏ���������

		bool Successinit = false;						// �����������t���O
		bool LoopFlag = true;							// updateloop�t���O

		std::shared_ptr<AudioResources> AudioSource;	// �I�[�f�B�I���
		
		std::string UseMaterialAtt;						// �}�e���A���̐ݒ�
		std::string Filepath;							// �t�@�C���p�X

		// OpenAL���
		std::array<ALuint,2> Buffers;					// �o�b�t�@�̐ݒ�
		ALuint Source;									// Source�̐ݒ�
		
		std::vector<AudioEffects*> EffectSlot;		// �G�t�F�N�g�X���b�g
		
		ALfloat Volume;								// �{�����[��

		AudioCommand* BufferCommand;	// �o�b�t�@���̃R�}���h
	};

}