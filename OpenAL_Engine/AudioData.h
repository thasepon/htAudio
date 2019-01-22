#pragma once

#include<Windows.h>
#include<string>
#include<vector>
#include<list>

namespace htAudio
{
	// ================= ↓定数型 =================== //
	#define USE_OGG_LIB

	// ================= ↓列挙型 =================== //
	
	// ファイル拡張子
	enum RIFFType
	{
		RIFF_WAV,
		RIFF_OGG,
		RIFF_MAX
	};

	// バッファのロードタイプ
	enum AudioLoadType
	{
		STREAM_LOAD,
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
		MAX_EFFECTS,
	};

	enum ORDERTYPE 
	{
		PLAY,
		STOP,
		PAUSE,
		MAX_ORDER
	};

	// ================= ↓構造体 =================== //

	struct OrderFormat
	{
		UINT16 SourceID;
		UINT16 Latency;
	};

	struct RIFFChunk
	{
		UCHAR RIFFID[4];
		WORD FileSize;
		UCHAR WaveFormatType[4];
	};

	struct FormatChunk
	{
		UCHAR FmtID[4];		// fmtチャンク
		unsigned long ChunkSize;// fmtチャンクのバイト数
		WORD FormatType;		// PCMの種類
		WORD Channels;			// チャンネル数
		DWORD SamplesPerSec;	// サンプリングレート
		DWORD BytesPerSec;	// データ転送速度
		WORD  BlockSize;		// ブロックサイズ
		WORD  BitsPerSample;	// サンプルあたりのビット数
	};

	struct DataChunk
	{
		UCHAR DataID[4];			// fmtチャンク
		std::size_t DataChunkSize;	// データバッファサイズ
		std::size_t BufData;
	};

	// ヘッダー情報
	struct AUDIOFILEFORMAT{
		RIFFChunk Riff;
		FormatChunk Fmt;
		DataChunk Data;
		long FirstSampleOffSet; // Bufferの開始位置
		std::size_t DataChunkSample; // サンプリング情報
	};

	// サウンドそのものの情報
	struct SoundType {
		int AudioID;				// Audioの情報
		std::string AudioName;		// オーディオファイルの名前
		double b3DAudio;			// 3DAudioを使用するかどうか
		std::string Cue;			// Cueの名前
		std::string SubGroup;		// 属しているグループ
		std::string MaterialObj;	// 属しているマテリアル
		bool Loopflag;				// ループフラグ
		AudioLoadType StreamType;	// ストリーミングタイプ
		RIFFType RIFFType;			// ファイル拡張子の種類
		double LowVolume;			// 最低音量
		double DefaultVolume;		// デフォルト音量
		double MaxVolume;			// 最大音量
		bool CreateFlag;			// 作成フラグ
	};

	// Audioが保持している情報
	struct AudioData {
		std::string Filepath;				// ファイルパス
		std::string	PresetSoundName;		// オーディオファイル名
		int PlayTime;						// 再生時間
		bool LoopSound;						// ループ情報
		long TotalreadBufSize;				// 読みこんだバッファ量
		long ReadBufSize;					// 一度に読み込むバッファ量
		std::size_t NextFirstSample = { 0 };
		std::size_t SubmitTimes = { 0 };	// どのバッファを使用するかの判定
		std::size_t BufferSample = { 0 };
	};

	// AudioInfo
	struct AudioResources
	{
		bool HasGotWaveFormat;		// オーディオファイルの情報を取得出来ているかどうか
		AudioData Data;				// Audioのデータ(使いまわしする予定)
		AUDIOFILEFORMAT Format;		// ヘッダー情報
		std::vector<SoundType> Soundtypes;		// XMLから得た情報(複数のデータがあります)
		std::vector<char> PrimaryMixed;	// バッファ保存[1]
		std::vector<char> SecondMixed;	// バッファ保存[2]
	};

}