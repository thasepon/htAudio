#include "AudioSpeaker.h"
#include"../../SpeakerHandler.h"
#include"../OpenAlCore/OpenALDevice.h"
#include"../AudioFormatData/AudioFormatData.h"
#include <algorithm>
#include<iterator>

namespace htAudio {

	//
	//	初期のサウンド指定無しでの動作
	//
	AudioSpeaker::AudioSpeaker() 
	{
		// 初期化終了
		Successinit = true;
	}

	//
	//	名前でサウンドを指定した初期化
	//
	AudioSpeaker::AudioSpeaker(string SoundName)
	{
		SetAudioSorce(SoundName);
		
		// 初期化終了
		Successinit = true;
	}

	//
	//	IDでサウンドを指定した初期化
	//
	AudioSpeaker::AudioSpeaker(int id)
	{
		SetAudioSorce(id);

		// 初期化終了
		Successinit = true;
	}
	
	//
	//	終了処理
	//
	AudioSpeaker::~AudioSpeaker()
	{
		// バッファの数を検索
		if (AudioSource.Soundtypes[NowUsedNumb].StreamType == false)
		{
			alDeleteBuffers(1, &Buffers[0]);
			alDeleteSources(1, &Source);
		}
		else {
			alDeleteBuffers(2, &Buffers.front());
			alDeleteSources(2, &Source);
		}
	}

	//
	//	
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
		if (AudioResource.Soundtype.StreamType == false)
		{
			alGenBuffers(1, &Buffers[0]);
			alGenSources(1, &Source);
			SetBuffer(Buffers[0]);
			alSourcei(Source, AL_BUFFER, Buffers[0]);
		}else{
			alGenBuffers(2, &Buffers[0]);
			alGenSources(1, &Source);
			SetBuffer(Buffers[0]);
			SetBuffer(Buffers[1]);
			alSourceQueueBuffers(Source, 2, &Buffers[0]);
		}


		// ソースの初期設定
		alSourcei(Source,AL_SOURCE_RELATIVE,AL_TRUE);

	}

	//
	bool AudioSpeaker::SetBuffer(ALuint Buf)
	{
		if (!Buf) {
			alGenBuffers(1, &Buf);
		}

		// バッファの更新
		ALenum format = AudioSource->GetAudioChannel() == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		int fq = AudioSource->GetAudioSpS();
		ALsizei size = (ALsizei)AudioSource->GetAudioBufferSize();

		alBufferData(Buf, format, AudioSource->GetBuffer(), size, fq);
		return true;
	}

	bool AudioSpeaker::Update()
	{
		// バッファの更新
		if (AudioResource.Soundtype.StreamType == false)
		{
			int State = 0;
			alGetSourcei(Source, AL_SOURCE_STATE, &State);
			if (State != AL_PLAYING && AudioResource.LoopSound == 1)
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
				printf("バッファ更新中\n");
				AudioSource->Update();
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
		if (AudioResource.Soundtype.Soundinfo[id].Extension == "wav")
		{
			std::shared_ptr<CLoadSoundFile> shard(new CLoadWave(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype, filepath));
			AudioSource = shard;
		}
		else if (AudioResource.Soundtype.Soundinfo[id].Extension == "ogg")
		{
			std::shared_ptr<CLoadSoundFile> shard(new CLoadOgg(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype, filepath));
			AudioSource = shard;
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