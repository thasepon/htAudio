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
	/// Deviceの管理とスピーカーの管理をするクラス
	/// </summary>
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		void AddSpeaker(UINT16 id,AudioSpeaker* ptr);		// スピーカーの追加
		void RemoveSpeaker( int numb );						// スピーカーの削除
		void AllSpeakerRemove();							// 登録されているスピーカーの全削除
		void SetAudioOrder(ORDERTYPE type, OrderFormat fmt);	// Audioのコマンドを保存していく
		void ClearAudioOrder();								// セットされたオーディオデータの削除

	private:
		void ThreadUpdate();					// スレッド更新
		void ExecOrderCmd();					// コマンドの消化

	private:
		list<AudioCommand*> OrderList;			// オーディオオーダー
		map<UINT16,AudioSpeaker*> SpeakerMap;	// 現在のスピーカーの設定
		thread UpdateThread;					// 非同期更新用
		bool Updateflag;						// 非同期更新フラグ

	};

}