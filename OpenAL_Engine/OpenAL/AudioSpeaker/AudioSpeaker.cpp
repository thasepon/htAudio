#include "AudioSpeaker.h"

#include"../AudioFormatData/AudioFormatData.h"
#include"../../AudioDecoder.h"
#include"../../EffectManager.h"
#include <algorithm>
#include<iterator>

namespace htAudio {

	//
	//	初期のサウンド指定無しでの動作
	//
	AudioSpeaker::AudioSpeaker()
	{
		HeaderFormat.HasGotWaveFormat = false;
		NowUsedNumb = 0;
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	AudioSpeaker::~AudioSpeaker()
	{
		// バッファとソースの削除
		if (SoundDatas[NowUsedNumb].StreamType == false)
		{
			if(Buffers[0] != 0)
				alDeleteBuffers(1, &Buffers[0]);
			
			if(Source != 0)
				alDeleteSources(1, &Source);
		}
		else {
			if (Buffers[0] != 0 || Buffers[1] != 0)
				alDeleteBuffers(2, Buffers);
			
			if (Source != 0)
				alDeleteSources(1, &Source);
		}

		SoundDatas.clear();
		PrimaryMixed.clear();
		SecondMixed.clear();
	}

	//
	//	現在対象にしているマテリアルの設定
	//
	void AudioSpeaker::SetMaterial(string Name)
	{
		// 現在のマテリアルと同じの場合は読み込みはしない
		if (UseMaterialAtt == Name)
		{
			printf("同一マテリアルです\n");
			return;
		}

		UseMaterialAtt = Name;

		HeaderFormat.HasGotWaveFormat = AudioFormatData::LoadAudioFormatData(SpeakerCue, SoundDatas, CueName);
		
		// ヘッダー取得に失敗
		if (!HeaderFormat.HasGotWaveFormat)
		{
			printf("マテリアル変更後の情報を取得に失敗\n");
			return;
		}

		ReadHeaderInfo();

	}

	/// <summary>
	/// オーディオファイルの指定と読み込みの設定
	/// オーディオフォーマット情報の読み込みとヘッダー部分のデコードをします。
	/// </summary>
	/// <param name="SoundName">オーディオファイル名</param>
	void AudioSpeaker::SetAudioSorce(string filename)
	{
		int cnt = 0;
		StreamBufSize = 4096;
		
		if (BufferCommand == nullptr)
		{
			BufferCommand.reset(new SetBufCommand());
		}
		
		if (EffectCommand == nullptr)
		{
			EffectCommand.reset(new AddEffectCommand());
		}

		// 同じファイルのセットは弾く
		if (CueName == filename)
		{
			printf("指定のファイルは既に読み込み済みです\n");
			return;
		}

		CueName = filename;

		HeaderFormat.HasGotWaveFormat = false;

		// オーディオ情報を外部ファイルから取得
		HeaderFormat.HasGotWaveFormat = AudioFormatData::LoadAudioFormatData(SpeakerCue,SoundDatas, CueName);

		if (!HeaderFormat.HasGotWaveFormat)
		{
			printf("SetAudioSorceの設定に失敗しました\n");
			return;
		}

		ReadHeaderInfo();

		//AddEffects();
		//Init();
	}

	/// <summary>
	/// オーディオファイルの指定と読み込みの設定
	/// オーディオフォーマット情報の読み込みとヘッダー部分のデコードをします。
	/// </summary>
	/// <param name="id">オーディオファイルID</param>
	void AudioSpeaker::SetAudioSorce(int id)
	{
		int cnt = 0;
		HeaderFormat.HasGotWaveFormat = false;
		StreamBufSize = 4096;

		CueId = id;

		if (BufferCommand == nullptr)
		{
			BufferCommand.reset(new SetBufCommand());
		}

		if (EffectCommand == nullptr)
		{
			EffectCommand.reset(new AddEffectCommand());
		}

		// オーディオ情報を外部ファイルから取得
		HeaderFormat.HasGotWaveFormat = AudioFormatData::LoadAudioFormatData(SpeakerCue, SoundDatas, CueName);

		if (!HeaderFormat.HasGotWaveFormat)
		{
			return;			// フォーマット取得できていません。
		}

		ReadHeaderInfo();

		//AddEffects();
		//Init();
	}

	/// <summary>
	/// ボリュームを設定
	/// </summary>
	/// <param name="volume"></param>
	void AudioSpeaker::SetVolume(double volume)
	{
		if (volume < 0)
		{
			volume = 0;
		}

		SpeakerCue.Volume = SoundDatas[NowUsedNumb].MaxVolume * volume;
	}

	/// <summary>
	/// ヘッダー情報の読み込み関数
	/// </summary>
	void AudioSpeaker::ReadHeaderInfo()
	{
		int cnt = 0;

		// マテリアルの設定があるかどうか
		if (UseMaterialAtt == "")
		{
			// マテリアル未設定処理
			// 番号を初期に設定+指定オーディオファイルのヘッダー読み込み
			NowUsedNumb = 0;
			DecodeAudioHeader();
		}
		else
		{
			// マテリアル設定されている場合
			for (auto itr : SoundDatas)
			{
				if (itr.MaterialObj != UseMaterialAtt)
				{
					cnt++;
					continue;
				}
				// マテリアルが見つかった場合の処理
				NowUsedNumb = cnt;
				DecodeAudioHeader();
				break;
			}
			// すべての情報を参照して見つからなかった場合は初期の音を鳴らす。
			if (cnt > SoundDatas.size())
			{
				NowUsedNumb = 0;
				DecodeAudioHeader();
			}
		}
	}

	/// <summary>
	/// 必要な情報の初期化と設定
	/// </summary>
	void AudioSpeaker::Init()
	{
		if (SoundDatas[NowUsedNumb].StreamType == PRE_LOAD)
		{
			// Preloadタイプ読み込み
			alGenBuffers(1, &Buffers[0]);
			alGenSources(1, &Source);
			alSourcei(Source, AL_BUFFER, Buffers[0]);
			SpeakerData.ReadBufSize = HeaderFormat.Data.ChunkSize;
			// TODO プリロードから取得する処理
		}else{
			// Streamloadタイプ読み込み
			InitStreamBuffer();
		}
	}

	/// <summary>
	/// 非同期処理なので注意すること
	/// バッファの更新とエフェクト情報の更新がメイン
	/// </summary>
	/// <returns></returns>
	bool AudioSpeaker::Update()
	{
		if (HeaderFormat.HasGotWaveFormat == false)
			return false;

		int State = 0;
		alGetSourcei(Source, AL_SOURCE_STATE, &State);

		// バッファの更新
		if (SoundDatas[NowUsedNumb].StreamType == PRE_LOAD)
		{
			alGetSourcei(Source, AL_SOURCE_STATE, &State);
			
			if (State != AL_PLAYING && SpeakerCue.Loopflag == 1)
			{
				alSourcei(Source, AL_LOOPING, true);
			}
		}
		else if (SoundDatas[NowUsedNumb].StreamType == STREAM_LOAD)
		{
			// バッファの更新
			DecodeAudioStreamBuffer();
		}

		// エフェクトの更新
		if (!EffectSlot.empty())
		{
			for (auto itr : EffectSlot) {
				itr->Update();
			}
		}

		// 更新終了
		return true;
	}

	/// <summary>
	/// 指定したオーディオのヘッダー情報を読み込む
	/// </summary>
	void AudioSpeaker::DecodeAudioHeader()
	{
		//ファイルから実際の情報を取得
		bool formatloadflag = false;

		formatloadflag = AudioDecoder::LoadRIFFFormat(HeaderFormat, SoundDatas[NowUsedNumb], SpeakerCue.Filepath);

		// 構造体の初期化設定
		SpeakerData.BufferSample = 0;
		SpeakerData.NextFirstSample = 0;
		SpeakerData.PlayTime = 0;
		SpeakerData.ReadBufSize = 0;
		SpeakerData.SubmitTimes = 0;
		SpeakerData.TotalreadBufSize = 0;

		// フォーマットに合わせたもの
		if (formatloadflag == true)
		{
			SpeakerData.DataChunkSample = HeaderFormat.Data.ChunkSize / HeaderFormat.Fmt.BlockSize;
			SpeakerData.NextFirstSample = HeaderFormat.FirstSampleOffSet;
		}
		else {
			SpeakerData.DataChunkSample = 0;
			SpeakerData.NextFirstSample = 0;
		}
	}

	/// <summary>
	/// 指定したオーディオからDataBufferを読み込む
	/// </summary>
	void AudioSpeaker::DecodeAudioStreamBuffer()
	{
		ALint State = 0;
		alGetSourcei(Source, AL_BUFFERS_PROCESSED, &State);

		// 再生終了バッファが存在する場合
		if (State > 0)
		{
			if (SpeakerData.SubmitTimes == 0)
			{
				UpdateStreamBuffer(PrimaryMixed);
			}
			else if (SpeakerData.SubmitTimes == 1)
			{
				UpdateStreamBuffer(SecondMixed);
			}
		}
	}

	/// <summary>
	/// ソース番号の取得
	/// </summary>
	/// <returns>使用しているID</returns>
	ALuint AudioSpeaker::GetSpeakerNumb()
	{ 
		return Source; 
	}

	/// <summary>
	/// どのボリュームタイプかを取得する
	/// </summary>
	/// <returns></returns>
	VOLUMETYPE AudioSpeaker::GetVolumeType()
	{
		return SpeakerCue.VolType;
	}

	/// <summary>
	/// エフェクトの追加処理
	/// </summary>
	/// <param name="effect">追加するエフェクト</param>
	/// <returns>成功しているかどうか</returns>
	bool AudioSpeaker::AddEffects()
	{
		if (SpeakerCue.CueEffect.size() == 0)
		{
			return;
		}

		// 読み込んだエフェクトを全て適応
		for (auto itr : SpeakerCue.CueEffect)
		{
			AudioEffects* ptr = EffectCommand->Execute(Source, itr.UseEffect, itr.UseElement);
			
			if (ptr != nullptr)
			{
				EffectSlot.push_back(ptr);
			}
		}
		return true;
	}
	
	/// <summary>
	/// StreamingLoad指定の場合の初期化
	/// </summary>
	void AudioSpeaker::InitStreamBuffer()
	{
		SpeakerData.ReadBufSize = StreamBufSize;

		// ソースを作成していない場合作成する
		if (Source == 0)
		{
			alGenSources(1, &Source);
		}

		// バッファが存在しない場合作成する
		if (Buffers[0] == 0)
		{
			alGenBuffers(2, Buffers);
		}

		// Primaryバッファの作成
		PrimaryMixed.clear();
		PrimaryMixed = std::vector<int16_t>(StreamBufSize);
		AudioDecoder::AudioBufferDecoder(&PrimaryMixed[0], SpeakerData, SoundDatas[NowUsedNumb], HeaderFormat, SpeakerCue.Filepath);
		
		// Secondバッファの作成
		SecondMixed.clear();
		SecondMixed = std::vector<int16_t>(StreamBufSize);	
		AudioDecoder::AudioBufferDecoder(&SecondMixed[0], SpeakerData, SoundDatas[NowUsedNumb], HeaderFormat, SpeakerCue.Filepath);
		
		// 作成したバッファの設定
		alSourceUnqueueBuffers(Source, 2, Buffers);
		BufferCommand->Execute(Buffers[0], HeaderFormat.Fmt.Channels, &PrimaryMixed[0], HeaderFormat.Fmt.SamplesPerSec, SpeakerData.ReadBufSize);
		alSourceQueueBuffers(Source, 1, &Buffers[0]);
		BufferCommand->Execute(Buffers[1], HeaderFormat.Fmt.Channels, &SecondMixed[0], HeaderFormat.Fmt.SamplesPerSec, SpeakerData.ReadBufSize);
		alSourceQueueBuffers(Source, 1, &Buffers[1]);
	}

	/// <summary>
	/// streamの更新バッファを更新
	/// </summary>
	void AudioSpeaker::UpdateStreamBuffer(std::vector<int16_t> buf)
	{
		bool readSuccessflag = false;
		
		if (readSuccessflag == true)
		{
			buf.clear();
			buf = std::vector<int16_t>(StreamBufSize);
			readSuccessflag = AudioDecoder::AudioBufferDecoder(&buf[0], SpeakerData, SoundDatas[NowUsedNumb], HeaderFormat, SpeakerCue.Filepath);

			// バッファのアップデート
			ALuint UpdateBufQue = 0;
			// バッファのデキュー
			alSourceUnqueueBuffers(Source, 1, &UpdateBufQue);
			// バッファの設定
			BufferCommand->Execute(UpdateBufQue, HeaderFormat.Fmt.Channels, &buf[0], HeaderFormat.Fmt.SamplesPerSec, SpeakerData.ReadBufSize);
			// バッファのインキュー
			alSourceQueueBuffers(Source, 1, &UpdateBufQue);
			// バッファの移動
			SpeakerData.SubmitTimes = !SpeakerData.SubmitTimes;
		}
	}


}