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


		AudioReSource* GetAudioResoucePtr();
		EffectManager* GetEffectElementPtr();
		SpeakerManager* GetSpeakerManagerPtr();

	private:
		void ThreadUpdate();							// スレッド更新

		list<AudioCommand*> OrderList;					// オーディオオーダー
		
		AudioReSource* ResourcePtr;			// Preloadでの使いまわし用のリソースptr
		EffectManager* EffectElementMgrPtr;	// エフェクトエレメントを保持するためのポインタ
		SpeakerManager* SpeakerMgrPtr;		// スピーカーマネージャーポインタ

		thread UpdateThread;						// 非同期更新用
		std::shared_ptr<DebugConsole> DConsolePtr;

		bool Updateflag;							// 非同期更新フラグ

	};

}