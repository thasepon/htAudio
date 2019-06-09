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
		ReleaseResource();
	}

	/// <summary>
	/// 最初にPreload設定の音声を読み込む
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{
		// Preloadステートの取得
		AudioFormatData::LoadAudioPreloadFormatData(Audioresourcelist);

		// 読み込んだ情報の分だけバッファの確保
		for(ResourceData itr : Audioresourcelist)
		{
			for (SoundType type : itr.soundType)
			{
				int16_t* buffer;
				AudioDecoder::AudioBufferDecoder(&buffer[0], itr.data, type, itr.fmt, itr.cueData.Filepath);
				itr.PreloadBuffer.push_back(*buffer);
			}
			
		}
	}

	/// <summary>
	/// 読み込んだbufferをクローン化して送る関数
	/// </summary>
	/// <param name=""></param>
	void AudioReSource::GetAudioBuffer(std::string cuename, AUDIOFILEFORMAT* fmt, std::list<SoundType>* type, AudioCue* cue, AudioData* data, void* buf)
	{
		for (ResourceData var : Audioresourcelist)
		{
			if (var.cueData.CueName == cuename)
			{
				fmt = &var.fmt;
				type = &var.soundType;
				cue = &var.cueData;
				data = &var.data;
				buf = &var.PreloadBuffer;
			}
		}
	}
	
	/// <summary>
	/// 読み込んだbufferをクローン化して送る関数
	/// </summary>
	/// <param name="Id"></param>
	void AudioReSource::GetAudioBuffer(int Id, AUDIOFILEFORMAT* fmt, std::list<SoundType>* type, AudioCue* cue, AudioData* data, void* buf)
	{
		for (ResourceData var : Audioresourcelist)
		{
			if (var.cueData.CueID == Id)
			{
				fmt = &var.fmt;
				type = &var.soundType;
				cue = &var.cueData;
				data = &var.data;
				buf = &var.PreloadBuffer;
			}
		}
	}

	/// <summary>
	/// 現在のリソースを全削除
	/// </summary>
	void AudioReSource::ReleaseResource()
	{
		if (Audioresourcelist.empty())
		{
			return;
		}
		
		for (ResourceData var : Audioresourcelist)
		{
			var.PreloadBuffer.clear();
			var.soundType.clear();
		}

		Audioresourcelist.clear();
	}

}