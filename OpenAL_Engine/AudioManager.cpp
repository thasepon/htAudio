#include "AudioManager.h"

#include"PlayCommand.h"
#include"StopCommand.h"
#include"PauseCommand.h"

namespace htAudio {

	//
	//	スレッドの開始
	//
	AudioManager::AudioManager()
	{
		Updateflag = true;
		// Updateのスレッド化
		UpdateThread = std::thread(&AudioManager::ThreadUpdate , this);
	}

	//
	//	全、登録スピーカーの削除
	//
	AudioManager::~AudioManager()
	{
		SpeakerMgrPtr->AllDeleteSpeaker();
	}

	//
	//	更新スレッド
	//
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
		//全オーダーの削除
		for (auto var : OrderList)
		{
			delete var;
		}

		// リストのクリア
		OrderList.clear();
	}

	//
	//	AudioOrderの起動
	//
	void AudioManager::ExecOrderCmd()
	{
		// 全オーダーの起動
		for (auto var : OrderList)
		{
			if (var->Execute() == true)
			{
				// オーダー完了と削除
			}
		}
	}
}