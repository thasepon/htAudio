#pragma once

#include<iostream>
#include<string>
#include<tchar.h>

#include"../../AudioData.h"
#include"../../AudioEffects.h"

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
		
		// 各種エフェクトのデータを呼び込
		// エフェクトの分だけオーバーライドしないとダメな気がする
		static bool LoadEffectData(CHORUS_INFO& info,std::string effectelementpath);
		static bool LoadEffectData(DISTORTION_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(ECHO_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(EQ_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(FLANGER_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(FQ_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(PITCH_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(REVERB_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(WAH_INFO& info, std::string effectelementpath);

	private:


	};

}