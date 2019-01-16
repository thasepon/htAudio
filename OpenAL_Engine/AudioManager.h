#pragma once

#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"

#include"AudioOrder.h"
#include"AudioCommand.h"

#include<map>
#include<utility>
#include<functional>
#include<list>

namespace htAudio {

	using namespace std;

	/// <summary>
	/// Device�̊Ǘ��ƃX�s�[�J�[�̊Ǘ�������N���X
	/// </summary>
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		void AddSpeaker(UINT16 id,AudioSpeaker* ptr);		// �X�s�[�J�[�̒ǉ�
		void RemoveSpeaker( int numb );						// �X�s�[�J�[�̍폜
		void AllSpeakerRemove();							// �o�^����Ă���X�s�[�J�[�̑S�폜
		void SetAudioOrder(ORDERTYPE type, OrderFormat fmt);	// Audio�̃R�}���h��ۑ����Ă���
		void ClearAudioOrder();								// �Z�b�g���ꂽ�I�[�f�B�I�f�[�^�̍폜

	private:
		void ThreadUpdate();					// �X���b�h�X�V
		void ExecOrderCmd();					// �R�}���h�̏���

	private:
		list<AudioCommand*> OrderList;			// �I�[�f�B�I�I�[�_�[
		map<UINT16,AudioSpeaker*> SpeakerMap;	// ���݂̃X�s�[�J�[�̐ݒ�
		thread UpdateThread;					// �񓯊��X�V�p
		bool Updateflag;						// �񓯊��X�V�t���O

	};

}