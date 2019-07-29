#include "AudioReSource.h"
#include"OpenAL/AudioFormatData/AudioFormatData.h"
#include <algorithm>

namespace htAudio
{
	/// <summary>
	/// コンストラクタでAudioバッファの読み込み
	/// </summary>
	AudioReSource::AudioReSource()
	{
		ReadCueFormatData();
		ReadPreLoadAudio();
	}

	AudioReSource::~AudioReSource()
	{
		ReleaseResource();
		ReleaseFormatData();
	}

#pragma region Buffer関係
	/// <summary>
	/// 最初にPreload設定の音声を読み込む
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{
		// Preloadステートの取得
		if (Audioresourcelist.empty())
			return;

		// 読み込んだ情報の分だけバッファの確保
		for(AudioCue itr : Audioresourcelist)
		{
			for (SoundType type : itr.AudioInfo)
			{
				long* buffer;
				
				// ヘッダー情報
				AudioDecoder::LoadRIFFFormat(type.AudioFormat,type, itr.Filepath);
				
				// バッファの取得
				AudioDecoder::AudioBufferDecoder(&buffer,nullptr,type, type.AudioFormat, itr.Filepath);
				
				// バッファの穂zン
				BufferMap.insert(std::make_pair(type.AudioID, buffer));
			}
		}
	}

	/// <summary>
	/// 読み込んだbufferをクローン化して送る関数
	/// </summary>
	/// <param name=""></param>
	void AudioReSource::GetAudioBuffer(SoundType Target, long* buf)
	{
		if (BufferMap.empty())
			return;

		for (auto var : BufferMap)
		{
			if (var.first == Target.AudioID)
			{
				*buf = *var.second;
				break;
			}
		}
	}
	
	/// <summary>
	/// 現在のリソースを全削除
	/// </summary>
	void AudioReSource::ReleaseResource()
	{
		if (BufferMap.empty())
			return;

		for (auto var : BufferMap)
		{
			delete var.second;
		}

		BufferMap.clear();
	}
#pragma endregion


#pragma region Format関係

	/// <summary>
	/// Cueのフォーマットデータを一括で読み込み
	/// </summary>
	void AudioReSource::ReadCueFormatData()
	{
		AudioFormatData::LoadAudioPreloadFormatData(Audioresourcelist);
	}

	/// <summary>
	/// 指定のCueデータを引っ張ってくる
	/// </summary>
	/// <param name="CueId"></param>
	AudioCue AudioReSource::GetFormatData(int CueId)
	{
		AudioCue selectCue;

		if (Audioresourcelist.empty())
			return selectCue;

		for (auto cue : Audioresourcelist)
		{
			if (cue.CueID != CueId)
				continue;

			selectCue = cue;
		}

		return selectCue;

	}

	/// <summary>
	/// 指定のCueデータを引っ張ってくる
	/// </summary>
	/// <param name="CueName"></param>
	AudioCue AudioReSource::GetFormatData(std::string CueName)
	{
		AudioCue selectCue;

		if (Audioresourcelist.empty())
			return selectCue;

		for (auto cue : Audioresourcelist)
		{
			if (cue.CueName != CueName)
				continue;

			selectCue = cue;
		}

		return selectCue;
	}

	/// <summary>
	/// 取得したフォーマットの破棄
	/// </summary>
	void AudioReSource::ReleaseFormatData()
	{
		if (Audioresourcelist.empty())
			return;

		for (auto cue : Audioresourcelist)
		{
			cue.CueEffect.clear();
			cue.AudioInfo.clear();
		}
		Audioresourcelist.clear();
	}
#pragma endregion


}