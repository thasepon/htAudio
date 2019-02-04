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
	/// Deviceの管理とスピーカーの管理をするクラス
	/// </summary>
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		void SetAudioOrder(ORDERTYPE type, OrderFormat fmt);// Audioのコマンドを保存していく
		void ExecOrderCmd();								// コマンドの消化
		void ClearAudioOrder();								// セットされたオーディオデータの削除

		shared_ptr<AudioReSource> GeteAudioResoucePtr() { return ResourcePtr; }
		shared_ptr<EffectManager> GetEffectElementPtr() { return EffectElementMgrPtr; }
		shared_ptr<SpeakerManager> GetSpeakerManagerPtr() { return SpeakerMgrPtr; }

	private:
		void ThreadUpdate();						// スレッド更新

		list<AudioCommand*> OrderList;				// オーディオオーダー
		
		shared_ptr<AudioReSource> ResourcePtr;					// Preloadでの使いまわし用のリソースptr
		shared_ptr<EffectManager> EffectElementMgrPtr;	// エフェクトエレメントを保持するためのポインタ
		shared_ptr<SpeakerManager> SpeakerMgrPtr;				// スピーカーマネージャーポインタ

		thread UpdateThread;						// 非同期更新用
		bool Updateflag;							// 非同期更新フラグ

	};

}