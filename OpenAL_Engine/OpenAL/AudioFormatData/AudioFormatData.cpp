#include "AudioFormatData.h"
#include"../../DLL/include/json/picojson.h"

#include<iostream>
#include <fstream>
#include <sstream>

namespace htAudio {
	
	AudioFormatData::AudioFormatData()
	{
	}


	AudioFormatData::~AudioFormatData()
	{

	}

	bool AudioFormatData::LoadAudioFormatData(AudioCue& cue, std::vector<SoundType>& types, std::string filepath, std::string Soundname)
	{
		
		SoundType Format;
		std::string Path;	// ファイルパス

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン
		
		if (ifs.fail())
		{
			return false;
		}

		const std::string json((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val,json);
		if (err.empty() == false)
		{
			return false;
		}

		// 指定データ群の抜き出しをします
		picojson::array& array = Val.get<picojson::array>();	// 最上位配列の抜き出し
		for (const auto& itr : array)
		{
			if (itr.get< std::string >() == Soundname)
			{
				picojson::object obj = itr.get<picojson::object>();
				
				cue.CueID = obj["id"].get<int>();
				cue.CueName = obj["name"].get < std::string >();
				cue.VolType = (VOLUMETYPE)obj["volumetype"].get<int>();
				cue.Loopflag = obj["loopflag"].get<bool>();
				
				picojson::array& effectarray = obj["effects"].get<picojson::array>();
				for (auto effectitr : effectarray)
				{
					EffectState state;
					state.UseEffect = (EFFECTSNUM)effectitr.get<picojson::object>()["effect"].get<int>();
					state.UseElement = effectitr.get<picojson::object>()["element"].get<std::string>();
				}

				picojson::array& soundinfoarray = obj["soundinfo"].get<picojson::array>();
				for (auto infoitr : soundinfoarray)
				{
					picojson::object itrobj = infoitr.get<picojson::object>();

					Format.AudioID = itrobj["id"].get<int>();
					Format.AudioName = itrobj["name"].get<std::string>();
					Format.Cue = itrobj["cue"].get<std::string>();
					Format.MaterialObj = itrobj["material"].get<std::string>();
					Format.StreamType = (AudioLoadType)itrobj["loadtype"].get<int>();
					Format.RIFFType = (RIFFType)itrobj["riff"].get<int>();
					Format.DefaultVolume = itrobj["defaultvolume"].get<double>();
					Format.MaxVolume = itrobj["maxvolume"].get<double>();

					types.push_back(Format);
				}

			}
		}
		Format.CreateFlag = true;
		return true;
	}


	bool AudioFormatData::LoadAudioFormatData(AudioCue& cue, std::vector<SoundType>& types, std::string filepath, int id)
	{
		SoundType Format;

		std::string Path;	// ファイルパス設定
		
		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
		{
			return false;
		}

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// 指定データ群の抜き出しをします
		picojson::array& array = Val.get<picojson::array>();	// 最上位配列の抜き出し
		for (const auto& itr : array)
		{
			picojson::object obj = itr.get<picojson::object>();
			
			if (obj["id"].get<int>() == id)
			{
				cue.CueID = obj["id"].get<int>();
				cue.CueName = obj["name"].get < std::string >();
				cue.VolType = (VOLUMETYPE)obj["volumetype"].get<int>();
				cue.Loopflag = obj["loopflag"].get<bool>();

				picojson::array& effectarray = obj["effects"].get<picojson::array>();
				for (auto effectitr : effectarray)
				{
					EffectState state;
					state.UseEffect = (EFFECTSNUM)effectitr.get<picojson::object>()["effect"].get<int>();
					state.UseElement = effectitr.get<picojson::object>()["element"].get<std::string>();
				}

				picojson::array& soundinfoarray = obj["soundinfo"].get<picojson::array>();
				for (auto infoitr : soundinfoarray)
				{
					picojson::object itrobj = infoitr.get<picojson::object>();

					Format.AudioID = itrobj["id"].get<int>();
					Format.AudioName = itrobj["name"].get<std::string>();
					Format.Cue = itrobj["cue"].get<std::string>();
					Format.MaterialObj = itrobj["material"].get<std::string>();
					Format.StreamType = (AudioLoadType)itrobj["loadtype"].get<int>();
					Format.RIFFType = (RIFFType)itrobj["riff"].get<int>();
					Format.DefaultVolume = itrobj["defaultvolume"].get<double>();
					Format.MaxVolume = itrobj["maxvolume"].get<double>();

					types.push_back(Format);
				}

			}
		}


		Format.CreateFlag = true;
		return true;

	}


}