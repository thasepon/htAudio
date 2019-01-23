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
		AudioSpeaker();								// スピーカーのみを生成
		AudioSpeaker(string SoundName);				// 名前指定でソースを生成
		AudioSpeaker(int id);						// ID指定でソースを生成
		~AudioSpeaker();							// スピーカーの削除処理

		void SetMaterial(string Name);				// マテリアルデータの設定
		void SetAudioSorce(string SoundName);		// オーディオデータの設定 ファイル名
		void SetAudioSorce(int id);					// オーディオデータの設定 ID
		
		bool Update();								// 更新処理
		bool AddEffects(AudioEffects* effect);		// エフェクトの追加
		bool RemoveEffects(AudioEffects* effect);	// エフェクトの削除

		ALuint GetSpeakerNumb();					// ソースの番号を取得

	private:
		// === 関数 === //
		void Init();						// 共通初期化処理
		void RegistAudioSource(int numb);	// 指定したAudio情報からバッファを獲得
		
		void Play();						// 再生処理 [外部呼出しの予定は現在無し]
		void Stop();						// 停止処理 [外部呼出しの予定は現在無し]
		void Pause();						// 一時停止処理 [外部呼出しの予定は現在無し]

		
		// === 変数 === //
		bool Successinit = false;			// 初期化成功フラグ
		uint16_t NowUsedNumb;				// 現在使用しているSoundTypeの番号
		AudioResources AudioSource;			// オーディオ情報
		string UseMaterialAtt = "";			// 対象マテリアルの情報
		array<ALuint,2> Buffers;			// バッファの設定
		ALuint Source;						// Sourceの設定
		list<AudioEffects*> EffectSlot;		// エフェクトスロット

		AudioCommand* BufferCommand;		// バッファ設定コマンド


	};

}