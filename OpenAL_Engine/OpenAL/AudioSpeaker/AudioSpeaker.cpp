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
		StreamBufSize = 4096;
		BufferCommand = new SetBufCommand();
		EffectCommand = new AddEffectCommand();
		
 		Successinit = true;
	}

	//
	//	名前でサウンドを指定した初期化
	//
	AudioSpeaker::AudioSpeaker(string filename)
	{
		StreamBufSize = 4096;

		BufferCommand = new SetBufCommand();
		EffectCommand = new AddEffectCommand();

		SetAudioSorce(filename);
		Successinit = true;
	}

	//
	//	IDでサウンドを指定した初期化
	//
	AudioSpeaker::AudioSpeaker(int id)
	{
		StreamBufSize = 4096;

		BufferCommand = new SetBufCommand();
		EffectCommand = new AddEffectCommand();

		SetAudioSorce(id);
		Successinit = true;
	}
	
	//
	//	終了処理
	//
	AudioSpeaker::~AudioSpeaker()
	{
		delete BufferCommand;
		delete EffectCommand;

		if (SoundDatas.empty() == true)
			return;

		// バッファの数を特定
		if (SoundDatas[NowUsedNumb].StreamType == false)
		{
			alDeleteBuffers(1, &Buffers[0]);
			alDeleteSources(1, &Source);
		}
		else {
			alDeleteBuffers(2, &Buffers.front());
			alDeleteSources(1, &Source);
		}
	}

	//
	//	現在対象にしているマテリアルの設定
	//
	void AudioSpeaker::SetMaterial(string Name)
	{
		UseMaterialAtt = Name;
	}

	/// <summary>
	/// オーディオファイルの指定と読み込みの設定
	/// オーディオフォーマット情報の読み込みとヘッダー部分のデコードをします。
	/// </summary>
	/// <param name="SoundName">オーディオファイル名</param>
	void AudioSpeaker::SetAudioSorce(string filename)
	{
		int cnt = 0;
		
		// オーディオ情報を外部ファイルから取得
		AudioFormatData::LoadAudioFormatData(SpeakerCue,SoundDatas,filename);

		// オーディオフォーマットの取得
		if (SoundDatas.empty() == true)
			return;			// フォーマット取得できていません。

		ReadHeaderInfo();
		AddEffects();
		Init();
	}

	/// <summary>
	/// オーディオファイルの指定と読み込みの設定
	/// オーディオフォーマット情報の読み込みとヘッダー部分のデコードをします。
	/// </summary>
	/// <param name="id">オーディオファイルID</param>
	void AudioSpeaker::SetAudioSorce(int id)
	{
		// オーディオ情報をxmlから取得
		AudioFormatData::LoadAudioFormatData(SpeakerCue,SoundDatas, id);

		// オーディオフォーマットの取得
		if (SoundDatas.empty() == true)
			return;			// フォーマット取得できていません。

		ReadHeaderInfo();
		AddEffects();
		Init();
	}

	/// <summary>
	/// ボリュームを設定
	/// </summary>
	/// <param name="volume"></param>
	void AudioSpeaker::SetVolume(double volume)
	{
		SpeakerCue.Volume = SoundDatas[NowUsedNumb].MaxVolume*volume;
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
			// 登録バッファバッファは一つ
			alGenBuffers(1, &Buffers[0]);
			alGenSources(1, &Source);
			alSourcei(Source, AL_BUFFER, Buffers[0]);
			SpeakerData.ReadBufSize = HeaderFormat.Data.ChunkSize;
		}else{
			// Streamloadタイプ読み込み
			// 登録バッファは二つ
			alGenBuffers(2, &Buffers[0]);
			alGenSources(1, &Source);
			alSourceQueueBuffers(Source, 2, &Buffers[0]);
			SpeakerData.ReadBufSize = StreamBufSize;
		}

		// 3d属性の付与
		alSourcei(Source,AL_SOURCE_RELATIVE,AL_TRUE);
		DecodeAudioStreamBuffer();

	}

	/// <summary>
	/// 非同期処理なので注意すること
	/// バッファの更新とエフェクト情報の更新がメイン
	/// </summary>
	/// <returns></returns>
	bool AudioSpeaker::Update()
	{
		if (SoundDatas.empty())
			return false;

		// バッファの更新
		if (SoundDatas[NowUsedNumb].StreamType == PRE_LOAD)
		{
			int State = 0;

			alGetSourcei(Source, AL_SOURCE_STATE, &State);
			
			if (State != AL_PLAYING && SpeakerCue.Loopflag == 1)
			{
				alSourcei(Source, AL_LOOPING, true);
			}
		}
		else if (SoundDatas[NowUsedNumb].StreamType == STREAM_LOAD)
		{
			int State = 0;

			// 再生終了バッファの確認
			alGetSourcei(Source, AL_BUFFERS_PROCESSED, &State);

			// 再生終了バッファが存在する場合
			if (State > 0)
			{
				// バッファのアップデート
				UpdateBufQue = 0;
				// バッファのデキュー
				alSourceUnqueueBuffers(Source, 1, &UpdateBufQue);
				// バッファの更新
				DecodeAudioStreamBuffer();
				// バッファのインキュー
				alSourceQueueBuffers(Source, 1, &UpdateBufQue);
			}

		}

		// エフェクトの更新
		for(auto itr : EffectSlot) {
			itr->Update();
		};
		
		return true;
	}

	/// <summary>
	/// 指定したオーディオのヘッダー情報を読み込む
	/// </summary>
	void AudioSpeaker::DecodeAudioHeader()
	{
		AudioDecoder::LoadRIFFFormat(HeaderFormat, SoundDatas[NowUsedNumb], SpeakerCue.Filepath);
	}

	/// <summary>
	/// 指定したオーディオからDataBufferを読み込む
	/// </summary>
	void AudioSpeaker::DecodeAudioStreamBuffer()
	{
		bool readSuccessflag = false; 

		if (SpeakerData.SubmitTimes == 0)
		{
			readSuccessflag = AudioDecoder::AudioBufferDecoder(&PrimaryMixed, SpeakerData, SoundDatas[NowUsedNumb], HeaderFormat, SpeakerCue.Filepath);

			if (readSuccessflag == true)
			{
				SpeakerData.SubmitTimes = 1;
				// バッファのセット
				BufferCommand->Execute(UpdateBufQue, HeaderFormat.Fmt.Channels, &PrimaryMixed, HeaderFormat.Fmt.SamplesPerSec, SpeakerData.ReadBufSize);
			}
		}
		else if (SpeakerData.SubmitTimes == 0)
		{
			readSuccessflag = AudioDecoder::AudioBufferDecoder(&SecondMixed, SpeakerData, SoundDatas[NowUsedNumb], HeaderFormat, SpeakerCue.Filepath);

			if (readSuccessflag == true)
			{
				SpeakerData.SubmitTimes = 0;// バッファのセット
				BufferCommand->Execute(UpdateBufQue, HeaderFormat.Fmt.Channels, &SecondMixed, HeaderFormat.Fmt.SamplesPerSec, SpeakerData.ReadBufSize);
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
	/// 再生処理
	/// 登録しているソースを再生します。
	/// </summary>
	void AudioSpeaker::Play()
	{
		//alSourcePlay(Source);
	}

	/// <summary>
	/// 停止処理
	/// 登録しているソースを停止します。
	/// </summary>
	void AudioSpeaker::Stop()
	{
		//alSourceStop(Source);
	}

	/// <summary>
	/// 一時停止処理
	/// 登録しているソースを一時停止します。
	/// </summary>
	void AudioSpeaker::Pause()
	{
		//alSourcePause(Source);
	}

}