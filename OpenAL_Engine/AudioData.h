#pragma once

#include<Windows.h>
#include<string>
#include<vector>
#include<list>

namespace htAudio
{
	// ================= ↓グローバル =================== //

	// ================= ↓定数型 =================== //
	#define USE_OGG_LIB
	
	// ================= ↓列挙型 =================== //
	
	// ファイル拡張子
	enum RIFFType
	{
		RIFF_WAV = 0,
		RIFF_OGG,
		RIFF_MAX
	};

	// バッファのロードタイプ
	enum AudioLoadType
	{
		STREAM_LOAD = 0,
		PRE_LOAD,
		MAX_LOAD
	};

	// エフェクトの種類
	enum EFFECTSNUM
	{
		REVERB = 0,
		CHORUS,
		DISTORTION,
		ECHO,
		FLANGER,
		FQ,
		PITCH,
		WAH,
		EQ,
		I3DAUDIO,
		CONE,
		MAX_EFFECTS,
	};

	enum ORDERTYPE 
	{
		PLAY,
		STOP,
		PAUSE,
		MAX_ORDER
	};

	enum VOLUMETYPE
	{
		ALL,
		BGM,
		SE,
		VOICE,
		MAX_VOLUMETYPE
	};

	// ================= ↓構造体 =================== //

	struct OrderFormat
	{
		uint16_t SourceID;
		double Latency;
	};

	struct DataChunk
	{
		char ChunkID[4];	// fmtチャンク
		unsigned long ChunkSize;	// データバッファサイズ
	};

	struct RIFFChunk
	{
		char ChunkID[4];
		unsigned short ChunkSize;
		unsigned char FormatType[4];
	};

	struct FormatChunk
	{
		char ChunkID[4];			// fmtチャンク
		unsigned long ChunkSize;		// fmtチャンクのバイト数
		unsigned short FormatType;		// PCMの種類
		unsigned short Channels;		// チャンネル数
		unsigned long SamplesPerSec;	// サンプリングレート
		unsigned long BytesPerSec;		// データ転送速度
		unsigned short BlockSize;		// ブロックサイズ
		unsigned short BitsPerSample;	// サンプルあたりのビット数
	};

	// ファイルの情報
	struct AUDIOFILEFORMAT {
		RIFFChunk Riff;
		FormatChunk Fmt;
		DataChunk Data;
		long FirstSampleOffSet; // Bufferの開始位置
		bool HasGotWaveFormat;		// オーディオファイルの情報を取得出来ているかどうか
	};

	// リスナーコーンのステータス用
	struct ConeState
	{
		double ConeOuterGain;	// コーンの外部ゲイン数値
		double InnerAngle;		// 内部の角度
		double OuterAngle;		// 外部の角度
	};

	struct EffectState
	{
		EFFECTSNUM UseEffect;
		std::string UseElement;
	};


	// サウンドの初期値、設定情報
	struct SoundType {
		int AudioID;				// Audioの情報
		std::string AudioName;		// オーディオファイルの名前
		std::string Cue;			// Cueの名前
		std::string MaterialObj;	// 属しているマテリアル
		AudioLoadType StreamType;	// ストリーミングタイプ
		RIFFType RIFFType;			// ファイル拡張子の種類
		double DefaultVolume;		// デフォルト音量
		double MaxVolume;			// 最大音量
		bool CreateFlag;			// 作成フラグ
		bool Loopflag;				// ループフラグ
	};

	// Cue(Soundtypeの大まとめ)の構造体
	struct AudioCue
	{
		int CueID;							// Audioの情報
		std::string Filepath;				// ファイルパス
		std::string	CueName;				// Cueファイル名
		double Volume;						// ボリューム
		VOLUMETYPE VolType;					// ボリュームのタイプ
		bool Loopflag;						// ループフラグ
		std::vector<EffectState> CueEffect;	// Cueに適応させるエフェクトの一覧
	};

	// Speaker側の情報
	struct AudioData {
		int PlayTime;						// 再生時間
		long TotalreadBufSize;				// 読みこんだバッファ量
		long ReadBufSize;					// 一度に読み込むバッファ量
		unsigned long NextFirstSample = { 0 };
		unsigned long SubmitTimes = { 0 };	// どのバッファを使用するかの判定
		unsigned long BufferSample = { 0 };
		long DataChunkSample; // サンプリング情報
	};

	

}