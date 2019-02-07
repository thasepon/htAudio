#include "AudioManager.h"

#include"PlayCommand.h"
#include"StopCommand.h"
#include"PauseCommand.h"

namespace htAudio {

	static thread UpdateThread;						// �񓯊��X�V�p

	/// <summary>
	/// AudioMgr�̍쐬�ƍX�V�X���b�h�̊J�n
	/// </summary>
	AudioManager::AudioManager()
	{
		Updateflag = true;

		ResourcePtr = new AudioReSource();
		EffectElementMgrPtr = new EffectManager();
		SpeakerMgrPtr = new SpeakerManager();

		// Update�̃X���b�h��
		UpdateThread = std::thread(&AudioManager::ThreadUpdate , this);
	}

	/// <summary>
	/// �o�^����Ă���X�s�[�J�[�̑S�폜
	/// </summary>
	AudioManager::~AudioManager()
	{
		ClearAudioOrder();
		SpeakerMgrPtr->AllDeleteSpeaker();


		delete ResourcePtr;
		delete EffectElementMgrPtr;
		delete SpeakerMgrPtr;

	}

	
	/// <summary>
	/// �񓯊��X�V
	/// </summary>
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
		if (OrderList.empty())
			return;

		//�S�I�[�_�[�̍폜
		for (auto var : OrderList)
		{
			delete var;
		}

		// ���X�g�̃N���A
		OrderList.clear();
	}

	/// <summary>
	/// ���[���̎n���X�V
	/// </summary>
	void AudioManager::ExecOrderCmd()
	{
		if (OrderList.empty())
			return;

		// �S�I�[�_�[�̋N��
		for (auto var : OrderList)
		{
			if (var->Execute() == true)
			{
				// �I�[�_�[�����ƍ폜
				delete var;
				OrderList.remove(var);
			}
		}
	}

	AudioReSource* AudioManager::GeteAudioResoucePtr()
	{ 
		return ResourcePtr; 
	}

	EffectManager* AudioManager::GetEffectElementPtr()
	{ 
		return EffectElementMgrPtr; 
	}

	SpeakerManager* AudioManager::GetSpeakerManagerPtr()
	{ 
		return SpeakerMgrPtr; 
	}

}