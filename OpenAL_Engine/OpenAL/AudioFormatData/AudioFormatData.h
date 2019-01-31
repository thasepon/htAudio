#pragma once

#include<iostream>
#include<string>
#include<tchar.h>

#include"../../AudioData.h"

namespace htAudio
{
	/// <summary>
	/// 外部ファイルに保存してある情報を読み込む処理
	/// </summary>
	class AudioFormatData
	{
	public:
		AudioFormatData();
		~AudioFormatData();

		static bool LoadAudioFormatData(AudioCue& cue,std::vector<SoundType>& types, std::string filepath, std::string Soundname);
		static bool LoadAudioFormatData(AudioCue& cue, std::vector<SoundType>& types, std::string filepath, int id);
		
		// 各種エフェクトのデータを呼び込む
		static bool LoadEffectData();

	private:


	};

}