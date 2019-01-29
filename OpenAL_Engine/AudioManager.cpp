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
		AllSpeakerRemove();
	}

	//
	//	スピーカーの登録処理
	//
	void AudioManager::AddSpeaker(UINT16 id, AudioSpeaker* ptr)
	{
		// マップに設定
		SpeakerMap.insert( make_pair(id, ptr) );
	}

	//
	//	スピーカーの削除
	//
	void AudioManager::RemoveSpeaker(int numb)
	{
		// ID検索
		auto itr = SpeakerMap.find(numb);
		// あった場合の処理
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
	//	更新スレッド
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
	//	登録してあるスピーカーの全削除
	//
	void AudioManager::AllSpeakerRemove()
	{
		Updateflag = false;
		
		// スレッドのアップデートの終了待機
		UpdateThread.join();

		// SpeakerMapを全削除
		for (auto var : SpeakerMap)
		{
			delete var.second;
		}
		SpeakerMap.clear();
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