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
		AllSpeakerRemove();
	}

	//
	//	�X�s�[�J�[�̓o�^����
	//
	void AudioManager::AddSpeaker(UINT16 id, AudioSpeaker* ptr)
	{
		// �}�b�v�ɐݒ�
		SpeakerMap.insert( make_pair(id, ptr) );
	}

	//
	//	�X�s�[�J�[�̍폜
	//
	void AudioManager::RemoveSpeaker(int numb)
	{
		// ID����
		auto itr = SpeakerMap.find(numb);
		// �������ꍇ�̏���
		if (SpeakerMap.end() != itr)
		{
			delete SpeakerMap[numb];
			SpeakerMap.erase(itr);
		}
	}

	void AudioManager::RemoveSpeaker(AudioSpeaker* ptr)
	{
		for (auto itr : SpeakerMap)
		{
			if (itr.second == ptr)
			{
				delete itr.second;
				SpeakerMap.erase(itr.first);
			}
		}

	}

	//
	//	�X�V�X���b�h
	//
	void AudioManager::ThreadUpdate()
	{
		while (Updateflag)
		{
			for (auto itr = SpeakerMap.begin(); itr != SpeakerMap.end(); itr++)
			{
				itr->second->Update();
			}
		}
	}

	//
	//	�o�^���Ă���X�s�[�J�[�̑S�폜
	//
	void AudioManager::AllSpeakerRemove()
	{
		Updateflag = false;
		
		// �X���b�h�̃A�b�v�f�[�g�̏I���ҋ@
		UpdateThread.join();

		// SpeakerMap��S�폜
		for (auto var : SpeakerMap)
		{
			delete var.second;
		}
		SpeakerMap.clear();
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