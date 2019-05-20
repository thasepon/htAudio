#include "AudioReSource.h"
#include"OpenAL/AudioFormatData/AudioFormatData.h"

namespace htAudio
{
	/// <summary>
	/// コンストラクタでAudioバッファの読み込み
	/// </summary>
	AudioReSource::AudioReSource()
	{
		ReadPreLoadAudio();
	}

	AudioReSource::~AudioReSource()
	{
		if (Audioresourcelist.size() <= 0)
			return;

		Audioresourcelist.clear();

	}

	/// <summary>
	/// 最初にPreload設定の音声を読み込む
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{
		// Preloadステートの取得
		AudioFormatData::LoadAudioPreloadFormatData(Audioresourcelist);

		// バッファの確保
		for(ResourceData itr : Audioresourcelist)
		{
			AudioDecoder::AudioBufferDecoder(&itr.preloadBuf[0], itr.data, SoundDatas[NowUsedNumb], itr.fmt, SpeakerCue.Filepath);
		}

	}

	/// <summary>
	/// 読み込んだbufferを取得する関数
	/// </summary>
	/// <param name=""></param>
	void AudioReSource::GetAudioBuffer(std::string)
	{
	}
	
	/// <summary>
	/// 読み込んだbufferを取得する関数
	/// </summary>
	/// <param name="Id"></param>
	void AudioReSource::GetAudioBuffer(int Id)
	{

	}

	/// <summary>
	/// 現在のリソースを全削除
	/// </summary>
	void AudioReSource::ReleaseResource()
	{

	}

}