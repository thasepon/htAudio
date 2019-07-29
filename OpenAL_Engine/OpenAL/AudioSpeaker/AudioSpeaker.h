#pragma once

#include"../../AudioData.h"
#include"../../AudioReSource.h"
#include"../../AudioEffects.h"

#include"../../SetBufCommand.h"
#include"../../AddEffectCommand.h"

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
		~AudioSpeaker();							// スピーカーの削除処理

		bool SetMaterialName(string Name);			// マテリアルデータの設定

		void SetAudioSorce(string filename);		// オーディオデータの設定 ファイル名
		void SetAudioSorce(int id);					// オーディオデータの設定 ID
		
		void SetVolume(double volume);				// ボリュームの設定
		
		bool Update();								// 更新処理
		
		ALuint GetSpeakerNumb();					// ソースの番号を取得
		VOLUMETYPE GetVolumeType();					// Cueのボリュームタイプを取得
		
	private:
		// === 関数 === //
		void Init();						// 共通初期化処理
		void DecodeAudioHeader();			// 指定したAudio情報からヘッダー情報を取得
		void DecodeAudioStreamBuffer();		// 指定したAudio情報からバッファを獲得
		void InitStreamBuffer();			// 指定Audioがstreamタイプだった場合の初期化準備
		void ReadHeaderInfo();				// ヘッダー情報の読み込み
		bool AddEffects();					// エフェクトの適応と設定
		void UpdateStreamBuffer(void* buf);				// バッファ更新用関数

		// === 構造体宣言 === //
		AudioData SpeakerData;					// Audioのデータ(使いまわしする予定)
		AUDIOFILEFORMAT HeaderFormat;			// ヘッダー情報
		AudioCue SpeakerCue;					// Jsonから得た情報(単一データ)
		std::vector<SoundType> SoundDatas;		// Jsonから得た情報(複数のデータがあります)
		AudioBuffer SpeakerBuffer;

		// === 変数 === //
		uint16_t NowUsedNumb;					// 現在使用しているSoundTypeの番号
		uint16_t StreamBufSize;					// バッファサイズ
		
		std::string UseMaterialAtt;				// 現在のマテリアル情報
		
		std::string CueName;					// 指定Cueの名前(CueIdだけでも可)
		int CueId;								// 指定CueのId(CueNameだけでも可)

		bool HasGotWaveFormat;					// フォーマット取得に成功しているか

		ALuint Source;							// Sourceの設定
		ALuint Buffers[2];						// バッファの設定

		std::shared_ptr <SetBufCommand> BufferCommand;	// バッファ設定用コマンド
		std::shared_ptr <AddEffectCommand> EffectCommand;	// エフェクトコマンド

		std::vector<AudioEffects*> EffectSlot;	// スピーカー適応するエフェクトスロット

	};

}