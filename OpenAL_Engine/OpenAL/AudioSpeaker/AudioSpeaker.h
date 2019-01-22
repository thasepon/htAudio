#pragma once

#include"../../AudioData.h"
#include"../../AudioReSource.h"
#include"../../AudioEffects.h"

#include"../../PlayCommand.h"
#include"../../StopCommand.h"
#include"../../PauseCommand.h"

#include<string>
#include<memory>
#include<array>
#include<functional>
#include<future>

#include<AL/efx.h>
#include<AL/efx-creative.h>

namespace htAudio
{
	using namespace std;

	/// <summary>
	/// サウンドの再生用クラス
	/// サウンド再生の窓口クラス
	/// </summary>
	class AudioSpeaker
	{
	public:
		AudioSpeaker();
		AudioSpeaker(string SoundName);	// 情報指定
		AudioSpeaker(int id);			// ID指定

		~AudioSpeaker();								// お片付け

		void SetMaterial(string Name);	// マテリアルデータの設定

		void SetAudioSorce(string SoundName);	// オーディオデータの設定 ファイル名
		void SetAudioSorce(int id);				// オーディオデータの設定 ID

		void Play();	// 再生処理
		void Stop();	// 停止処理
		void Pause();	// 一時停止処理
		
		bool Update();		// 更新処理
		void StartUpdate();	// 更新の開始
		void StopUpdate();	// 更新の停止

		bool AddEffects(AudioEffects* effect);		// エフェクトの追加
		bool RemoveEffects(AudioEffects* effect);	// エフェクトの追加

		uint16_t GetSpeakerNumb();					// ソースの番号を取得

	private:
		// === 関数 === //
		bool SetBuffer(uint8_t Buf);	// バッファの設定
		void Init();				// 共通初期化処理
		
		// === 変数 === //
		bool Successinit = false;	// 初期化成功フラグ
		bool UpdateFlag = false;	// 更新フラグ

		AudioResources AudioSource;	// オーディオ情報
		string UseMaterialAtt;		// 対象マテリアルの情報
		array<uint16_t,2> Buffers;	// バッファの設定
		uint16_t Source;					// Sourceの設定
		list<AudioEffects*> EffectSlot;	// エフェクトスロット
		double Volume;					// ボリューム
		AudioCommand* BufferCommand;	// バッファ回りのコマンド
	};

}