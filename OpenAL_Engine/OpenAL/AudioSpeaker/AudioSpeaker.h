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
		AudioSpeaker(string filename);				// 名前指定でソースを生成
		AudioSpeaker(int id);						// ID指定でソースを生成
		~AudioSpeaker();							// スピーカーの削除処理

		void SetMaterial(string Name);				// マテリアルデータの設定
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
		void DecodeAudioBuffer();			// 指定したAudio情報からバッファを獲得
		void ReadHeaderInfo();				// ヘッダー情報の読み込み
		bool AddEffects();					// エフェクトの適応と設定

		void Play();						// 再生処理 ※[外部呼出しの予定は現在無し:Not_Used]
		void Stop();						// 停止処理 ※[外部呼出しの予定は現在無し:Not_Used]
		void Pause();						// 一時停止処理 ※[外部呼出しの予定は現在無し:Not_Used]

		// === 変数 === //
		bool Successinit = false;				// 初期化成功フラグ
		uint16_t NowUsedNumb;					// 現在使用しているSoundTypeの番号
		
		AudioData SpeakerData;					// Audioのデータ(使いまわしする予定)
		AUDIOFILEFORMAT HeaderFormat;			// ヘッダー情報
		std::vector<SoundType> SoundDatas;		// XMLから得た情報(複数のデータがあります)
		AudioCue SpeakerCue;					// XMLから得た情報(単一データ)

		std::vector<char> PrimaryMixed;			// バッファ保存[1]
		std::vector<char> SecondMixed;			// バッファ保存[2](Preloadの場合は未使用)
		std::string UseMaterialAtt;				// 現在のマテリアル情報

		ALuint Source;							// Sourceの設定
		ALuint UpdateBufQue;					// インキューデキューするバッファの選択
		array<ALuint,2> Buffers;				// バッファの設定

		unique_ptr<SetBufCommand> BufferCommand;	// バッファ設定用コマンド
		unique_ptr<AddEffectCommand> EffectCommand;	// エフェクトコマンド

		std::vector<AudioEffects*> EffectSlot;	// スピーカー適応するエフェクトスロット
	};

}