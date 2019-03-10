#pragma once

#include"AudioOrder.h"
#include"AudioCommand.h"
#include"AudioReSource.h"
#include"EffectManager.h"
#include"SpeakerManager.h"
#include"AudioDecoder.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

#include<memory>
#include<map>
#include<utility>
#include<functional>
#include<list>
#include"DebugConsole.h"

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


		AudioReSource* GetAudioResoucePtr();
		EffectManager* GetEffectElementPtr();
		SpeakerManager* GetSpeakerManagerPtr();

	private:
		void ThreadUpdate();							// �X���b�h�X�V

		list<AudioCommand*> OrderList;					// �I�[�f�B�I�I�[�_�[
		
		AudioReSource* ResourcePtr;			// Preload�ł̎g���܂킵�p�̃��\�[�Xptr
		EffectManager* EffectElementMgrPtr;	// �G�t�F�N�g�G�������g��ێ����邽�߂̃|�C���^
		SpeakerManager* SpeakerMgrPtr;		// �X�s�[�J�[�}�l�[�W���[�|�C���^

		thread UpdateThread;						// �񓯊��X�V�p
		std::shared_ptr<DebugConsole> DConsolePtr;

		bool Updateflag;							// �񓯊��X�V�t���O

	};

}