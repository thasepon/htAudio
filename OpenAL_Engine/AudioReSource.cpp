#include "AudioReSource.h"

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
		if (AudioresourceMap.size() <= 0)
			return;

		AudioresourceMap.clear();

	}

	/// <summary>
	/// 最初にPreload設定の音声を読み込む
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{

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
	/// 現在使用している
	/// </summary>
	void AudioReSource::ReleaseResource()
	{

	}

}