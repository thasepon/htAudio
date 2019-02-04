#pragma once

#include"OpenAL/OpenAlCore/OpenALDevice.h"

#include"AudioOrder.h"
#include"AudioCommand.h"
#include"AudioReSource.h"
#include"EffectManager.h"
#include"SpeakerManager.h"

#include<memory>
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

		void SetAudioOrder(ORDERTYPE type, OrderFormat fmt);// Audio�̃R�}���h��ۑ����Ă���
		void ExecOrderCmd();								// �R�}���h�̏���
		void ClearAudioOrder();								// �Z�b�g���ꂽ�I�[�f�B�I�f�[�^�̍폜

		shared_ptr<AudioReSource> GeteAudioResoucePtr() { return ResourcePtr; }
		shared_ptr<EffectManager> GetEffectElementPtr() { return EffectElementMgrPtr; }
		shared_ptr<SpeakerManager> GetSpeakerManagerPtr() { return SpeakerMgrPtr; }

	private:
		void ThreadUpdate();						// �X���b�h�X�V

		list<AudioCommand*> OrderList;				// �I�[�f�B�I�I�[�_�[
		
		shared_ptr<AudioReSource> ResourcePtr;					// Preload�ł̎g���܂킵�p�̃��\�[�Xptr
		shared_ptr<EffectManager> EffectElementMgrPtr;	// �G�t�F�N�g�G�������g��ێ����邽�߂̃|�C���^
		shared_ptr<SpeakerManager> SpeakerMgrPtr;				// �X�s�[�J�[�}�l�[�W���[�|�C���^

		thread UpdateThread;						// �񓯊��X�V�p
		bool Updateflag;							// �񓯊��X�V�t���O

	};

}