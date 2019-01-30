#include "AudioManager.h"

#include"PlayCommand.h"
#include"StopCommand.h"
#include"PauseCommand.h"

namespace htAudio {

	//
	//	�X���b�h�̊J�n
	//
	AudioManager::AudioManager()
	{
		Updateflag = true;
		// Update�̃X���b�h��
		UpdateThread = std::thread(&AudioManager::ThreadUpdate , this);
	}

	//
	//	�S�A�o�^�X�s�[�J�[�̍폜
	//
	AudioManager::~AudioManager()
	{
		SpeakerMgrPtr->AllDeleteSpeaker();
	}

	//
	//	�X�V�X���b�h
	//
	void AudioManager::ThreadUpdate()
	{
		while (Updateflag)
		{
			SpeakerMgrPtr->SpeakerUpdate();
		}
	}

	//
	//	AudioOrder�̃Z�b�g
	//
	void AudioManager::SetAudioOrder(ORDERTYPE type, OrderFormat fmt)
	{
		switch (type)
		{
		case htAudio::PLAY:
			OrderList.push_back(new PlayCommand(fmt));
			break;
		case htAudio::STOP:
			OrderList.push_back(new StopCommand(fmt));
			break;
		case htAudio::PAUSE:
			OrderList.push_back(new PauseCommand(fmt));
			break;
		case htAudio::MAX_ORDER:
			// �G���[����
			break;
		default:
			break;
		}
		
	}

	//
	//	AudioOrder�̏�����
	//
	void AudioManager::ClearAudioOrder()
	{
		//�S�I�[�_�[�̍폜
		for (auto var : OrderList)
		{
			delete var;
		}

		// ���X�g�̃N���A
		OrderList.clear();
	}

	//
	//	AudioOrder�̋N��
	//
	void AudioManager::ExecOrderCmd()
	{
		// �S�I�[�_�[�̋N��
		for (auto var : OrderList)
		{
			if (var->Execute() == true)
			{
				// �I�[�_�[�����ƍ폜
			}
		}
	}
}