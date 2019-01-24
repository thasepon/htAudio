#include "AudioSpeaker.h"
#include"../../SpeakerHandler.h"
#include"../OpenAlCore/OpenALDevice.h"
#include"../AudioFormatData/AudioFormatData.h"
#include"../../AudioDecoder.h"
#include <algorithm>
#include<iterator>

#include"../../SetBufCommand.h"

namespace htAudio {

	//
	//	初期のサウンド指定無しでの動作
	//
	AudioSpeaker::AudioSpeaker() 
	{
		BufferCommand = new SetBufCommand();

		Successinit = true;
	}

	//
	//	名前でサウンドを指定した初期化
	//
	AudioSpeaker::AudioSpeaker(string SoundName)
	{
		BufferCommand = new SetBufCommand();
		
		SetAudioSorce(SoundName);
		Successinit = true;
	}

	//
	//	IDでサウンドを指定した初期化
	//
	AudioSpeaker::AudioSpeaker(int id)
	{
		BufferCommand = new SetBufCommand();

		SetAudioSorce(id);
		Successinit = true;
	}
	
	//
	//	終了処理
	//
	AudioSpeaker::~AudioSpeaker()
	{
		// バッファの数を特定
		if (AudioSource.Soundtypes[NowUsedNumb].StreamType == false)
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
	void AudioSpeaker::SetAudioSorce(string SoundName)
	{
		int cnt = 0;
		
		// オーディオ情報を外部ファイルから取得
		AudioSource.Soundtypes = AudioFormatData::GetAudioFormatData(AudioSource.Data.Filepath, SoundName);

		// オーディオフォーマットの取得
		if (AudioSource.Soundtypes.empty() == true)
			return;			// フォーマット取得できていません。

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
			for (auto itr : AudioSource.Soundtypes)
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
			if (cnt > AudioSource.Soundtypes.size())
			{
				NowUsedNumb = 0;
				DecodeAudioHeader();
			}

		}
		
	}

	/// <summary>
	/// オーディオファイルの指定と読み込みの設定
	/// オーディオフォーマット情報の読み込みとヘッダー部分のデコードをします。
	/// </summary>
	/// <param name="id">オーディオファイルID</param>
	void AudioSpeaker::SetAudioSorce(int id)
	{
		int cnt = 0;

		// オーディオ情報をxmlから取得
		AudioSource.Soundtypes = AudioFormatData::GetAudioFormatData(AudioSource.Data.Filepath, id);

		// オーディオフォーマットの取得
		if (AudioSource.Soundtypes.empty() == true)
			return; // フォーマット取得できていません。

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
			for (auto itr : AudioSource.Soundtypes)
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
			if (cnt > AudioSource.Soundtypes.size())
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
		if (AudioSource.Soundtypes[NowUsedNumb].StreamType == false)
		{
			// Preloadタイプ読み込み
			// 登録バッファバッファは一つ
			alGenBuffers(1, &Buffers[0]);
			alGenSources(1, &Source);
			alSourcei(Source, AL_BUFFER, Buffers[0]);
		}else{
			// Streamloadタイプ読み込み
			// 登録バッファは二つ
			alGenBuffers(2, &Buffers[0]);
			alGenSources(1, &Source);
			alSourceQueueBuffers(Source, 2, &Buffers[0]);
		}

		// 3d属性の付与
		alSourcei(Source,AL_SOURCE_RELATIVE,AL_TRUE);

	}

	/// <summary>
	/// 非同期処理なので注意すること
	/// バッファの更新とエフェクト情報の更新がメイン
	/// </summary>
	/// <returns></returns>
	bool AudioSpeaker::Update()
	{
		// バッファの更新
		if (AudioSource.Soundtypes[NowUsedNumb].StreamType == false)
		{
			int State = 0;
			alGetSourcei(Source, AL_SOURCE_STATE, &State);
			if (State != AL_PLAYING && AudioSource.Soundtypes[NowUsedNumb].Loopflag == 1)
			{
				Play();
			}
		}
		else 
		{
			int State = 0;
			alGetSourcei(Source, AL_BUFFERS_PROCESSED, &State);

			if (State > 0)
			{
				// バッファのアップデート
				ALuint Buf = 0;
				alSourceUnqueueBuffers(Source, 1, &Buf);
				SetBuffer(Buf);
				alSourceQueueBuffers(Source, 1, &Buf);
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
		AudioDecoder::LoadRIFFFormat();
	}

	/// <summary>
	/// 指定したオーディオからDataBufferを読み込む
	/// </summary>
	void AudioSpeaker::DecodeAudioBuffer()
	{
		// 引数説明	: ヘッダーフォーマット 、保存先data 、 拡張子 、使用バッファ
		AudioDecoder::AudioBufferDecoder(AudioSource, NowUsedNumb);
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
	/// エフェクトの追加処理
	/// </summary>
	/// <param name="effect">追加するエフェクト</param>
	/// <returns>成功しているかどうか</returns>
	bool AudioSpeaker::AddEffects(AudioEffects* effect)
	{
		EffectSlot.push_back(effect);
		return true;
	}
	
	/// <summary>
	/// 再生処理
	/// 登録しているソースを再生します。
	/// </summary>
	void AudioSpeaker::Play()
	{
		alSourcePlay(Source);
	}

	/// <summary>
	/// 停止処理
	/// 登録しているソースを停止します。
	/// </summary>
	void AudioSpeaker::Stop()
	{
		alSourceStop(Source);
	}

	/// <summary>
	/// 一時停止処理
	/// 登録しているソースを一時停止します。
	/// </summary>
	void AudioSpeaker::Pause()
	{
		alSourcePause(Source);
	}

}