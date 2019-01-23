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

	//
	//	オーディオ情報の取得と設定(名前)
	//
	void AudioSpeaker::SetAudioSorce(string SoundName)
	{
		// オーディオ情報をxmlから取得
		AudioSource.Soundtypes = AudioFormatData::GetAudioFormatData(AudioSource.Data.Filepath, SoundName);

		// オーディオフォーマットの取得
		if (AudioSource.Soundtypes.empty() == true)
		{
			// フォーマット取得できていません。
			return;
		}

		// マテリアルの設定があるかどうか
		if (UseMaterialAtt == "")
		{
			// マテリアル未設定
			NowUsedNumb = 0;
			RegistAudioSource(NowUsedNumb);
		}
		else
		{
			int cnt = 0;

			// マテリアル設定されている場合
			for (auto itr : AudioSource.Soundtypes)
			{
				// マテリアル名と同一
				if (itr.MaterialObj != UseMaterialAtt)
				{
					cnt++;
					continue;
				}

				// 番号を指定してバッファの読み込み
				NowUsedNumb = cnt;
				RegistAudioSource(NowUsedNumb);
			}

			// すべての情報を参照して見つからなかった場合は
			// 初期の音を鳴らす。
			if (cnt >= AudioSource.Soundtypes.size())
			{
				NowUsedNumb = 0;
				RegistAudioSource(NowUsedNumb);
			}

		}
		
	}

	//
	//	オーディオ情報の取得と設定(ID)
	//
	void AudioSpeaker::SetAudioSorce(int id)
	{
		// オーディオ情報をxmlから取得
		AudioSource.Soundtypes = AudioFormatData::GetAudioFormatData(AudioSource.Data.Filepath, id);

		// オーディオフォーマットの取得
		if (AudioSource.Soundtypes.empty() == true)
		{
			// フォーマット取得できていません。
			return;
		}

		// マテリアルの設定があるかどうか
		if (UseMaterialAtt == "")
		{
			// マテリアル未設定
			NowUsedNumb = 0;
			RegistAudioSource(NowUsedNumb);
		}
		else
		{
			int cnt = 0;

			// マテリアル設定されている場合
			for (auto itr : AudioSource.Soundtypes)
			{
				// マテリアル名と同一
				if (itr.MaterialObj != UseMaterialAtt)
				{
					cnt++;
					continue;
				}

				// 番号を指定してバッファの読み込み
				NowUsedNumb = cnt;
				RegistAudioSource(NowUsedNumb);
			}

			// すべての情報を参照して見つからなかった場合は
			// 初期の音を鳴らす。
			if (cnt >= AudioSource.Soundtypes.size())
			{
				NowUsedNumb = 0;
				RegistAudioSource(NowUsedNumb);
			}

		}



	}

	/// <summary>
	/// 初期バッファの作成とxmlから読み込んだ情報の設定
	/// </summary>
	void AudioSpeaker::Init()
	{
		if (AudioSource.Soundtypes[NowUsedNumb].StreamType == false)
		{
			alGenBuffers(1, &Buffers[0]);
			alGenSources(1, &Source);
			BufferCommand->Execute();
			alSourcei(Source, AL_BUFFER, Buffers[0]);
		}else{
			alGenBuffers(2, &Buffers[0]);
			alGenSources(1, &Source);
			BufferCommand->Execute();
			BufferCommand->Execute();
			alSourceQueueBuffers(Source, 2, &Buffers[0]);
		}

		// ソースの初期設定
		alSourcei(Source,AL_SOURCE_RELATIVE,AL_TRUE);

	}


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
		std::for_each(EffectSlot.begin(),EffectSlot.end(),[](AudioEffects* x) {
			x->Update();
		});
		
		return true;
	}

	void AudioSpeaker::Play()
	{
		alSourcePlay(Source);
	}

	void AudioSpeaker::Stop()
	{
		alSourceStop(Source);
	}

	void AudioSpeaker::Pause()
	{
		alSourcePause(Source);
	}

	void AudioSpeaker::RegistAudioSource(int numb)
	{
		// マテリアルの設定がない場合id[0]の音を鳴らす
		if (AudioSource.Soundtypes[numb].RIFFType == RIFF_WAV)
		{
			AudioDecoder::AudioBufferDecoder(AudioSource.Format, AudioSource.Data, RIFF_WAV, );
		}
		else if (AudioSource.Soundtypes[numb].RIFFType == RIFF_OGG)
		{
			AudioDecoder::AudioBufferDecoder(AudioSource.Format, AudioSource.Data, RIFF_OGG, );
		}
		Init();
	}

	ALuint AudioSpeaker::GetSpeakerNumb()
	{ 
		return Source; 
	}

	/// <summary>
	/// 概要		:: 外部からのエフェクト呼び出し用の関数
	/// アクセス制限	:: public
	/// </summary>
	bool AudioSpeaker::AddEffects(AudioEffects* effect)
	{
		EffectSlot.push_back(effect);
		return true;
	}

	bool AudioSpeaker::RemoveEffects(AudioEffects* effect)
	{
		for (auto itr : EffectSlot)
		{
			if (itr == effect)
			{
				delete itr;
				EffectSlot.remove(itr);
			}
		}
	}

}