#include "AudioManager.h"

#include"PlayCommand.h"
#include"StopCommand.h"
#include"PauseCommand.h"

namespace htAudio {

	static thread UpdateThread;						// 非同期更新用

	/// <summary>
	/// AudioMgrの作成と更新スレッドの開始
	/// </summary>
	AudioManager::AudioManager()
	{
		Updateflag = true;

		ResourcePtr = new AudioReSource();
		EffectElementMgrPtr = new EffectManager();
		SpeakerMgrPtr = new SpeakerManager();

		// Updateのスレッド化
		UpdateThread = std::thread(&AudioManager::ThreadUpdate , this);
	}

	/// <summary>
	/// 登録されているスピーカーの全削除
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
	/// 非同期更新
	/// </summary>
	void AudioManager::ThreadUpdate()
	{
		while (Updateflag)
		{
			SpeakerMgrPtr->SpeakerUpdate();
		}
	}

	//
	//	AudioOrderのセット
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
			// エラー処理
			break;
		default:
			break;
		}
		
	}

	//
	//	AudioOrderの初期化
	//
	void AudioManager::ClearAudioOrder()
	{
		if (OrderList.empty())
			return;

		//全オーダーの削除
		for (auto var : OrderList)
		{
			delete var;
		}

		// リストのクリア
		OrderList.clear();
	}

	/// <summary>
	/// おーだの始動更新
	/// </summary>
	void AudioManager::ExecOrderCmd()
	{
		if (OrderList.empty())
			return;

		// 全オーダーの起動
		for (auto var : OrderList)
		{
			if (var->Execute() == true)
			{
				// オーダー完了と削除
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