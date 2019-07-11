#include "AudioFormatData.h"
#include"../../DLL/include/json/picojson.h"


#include<iostream>
#include <fstream>
#include <sstream>
#include<Windows.h>

namespace htAudio {
	

	static std::string ExeDirectory;
	static std::string DataPath;

	AudioFormatData::AudioFormatData()
	{
	}


	AudioFormatData::~AudioFormatData()
	{

	}

	bool AudioFormatData::LoadAudioFormatData(AudioCue& cue, std::vector<SoundType>& types, std::string Soundname)
	{
		
		SoundType Format;
		std::string Path = CreateFormatSDataPath();

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
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == Soundname)
			{
				picojson::object obj = cueitr.second.get<picojson::object>();

				cue.CueID = (uint16_t)obj["id"].get<double>();
				cue.CueName = obj["name"].get < std::string >();
				cue.VolType = (VOLUMETYPE)((int)obj["volumetype"].get<double>());
				cue.Loopflag = obj["loopflag"].get<bool>();
				cue.Filepath = CreateAudioDataPath();
				cue.StreamType = (AudioLoadType)((int)obj["loadtype"].get<double>());

				picojson::array& effectarray = obj["effects"].get<picojson::array>();
				for (auto effectitr : effectarray)
				{
					EffectState state;
					state.UseEffect = (EFFECTSNUM)((int)effectitr.get<picojson::object>()["effect"].get<double>());
					state.UseElement = effectitr.get<picojson::object>()["element"].get<std::string>();
					cue.CueEffect.push_back(state);
				}

				picojson::array& soundinfoarray = obj["soundinfo"].get<picojson::array>();
				for (auto infoitr : soundinfoarray)
				{
					picojson::object itrobj = infoitr.get<picojson::object>();

					Format.AudioID = (uint16_t)itrobj["id"].get<double>();
					Format.AudioName = itrobj["name"].get<std::string>();
					Format.Cue = itrobj["cue"].get<std::string>();
					Format.MaterialObj = itrobj["material"].get<std::string>();
					Format.RIFFType = (RIFFType)((int)itrobj["riff"].get<double>());
					Format.DefaultVolume = itrobj["defaultvolume"].get<double>();
					Format.MaxVolume = itrobj["maxvolume"].get<double>();

					types.push_back(Format);
				}

				Format.CreateFlag = true;
			}
		}
		return true;
	}


	bool AudioFormatData::LoadAudioFormatData(AudioCue& cue, std::vector<SoundType>& types, int id)
	{
		SoundType Format;

		std::string Path = CreateFormatSDataPath();
		
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
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一idの物を検索
			picojson::object obj = cueitr.second.get<picojson::object>();

			if (obj["id"].get<double>() == id)
			{
				cue.CueID = (uint16_t)obj["id"].get<double>();
				cue.CueName = obj["name"].get < std::string >();
				cue.VolType = (VOLUMETYPE)((int)obj["volumetype"].get<double>());
				cue.Loopflag = obj["loopflag"].get<bool>();
				cue.Filepath = CreateAudioDataPath();
				cue.StreamType = (AudioLoadType)((int)obj["loadtype"].get<double>());

				picojson::array& effectarray = obj["effects"].get<picojson::array>();
				for (auto effectitr : effectarray)
				{
					EffectState state;
					state.UseEffect = (EFFECTSNUM)((int)effectitr.get<picojson::object>()["effect"].get<double>());
					state.UseElement = effectitr.get<picojson::object>()["element"].get<std::string>();
					cue.CueEffect.push_back(state);
				}

				picojson::array& soundinfoarray = obj["soundinfo"].get<picojson::array>();
				for (auto infoitr : soundinfoarray)
				{
					picojson::object itrobj = infoitr.get<picojson::object>();

					Format.AudioID = (uint16_t)itrobj["id"].get<double>();
					Format.AudioName = itrobj["name"].get<std::string>();
					Format.Cue = itrobj["cue"].get<std::string>();
					Format.MaterialObj = itrobj["material"].get<std::string>();
					Format.RIFFType = (RIFFType)((int)itrobj["riff"].get<double>());
					Format.DefaultVolume = itrobj["defaultvolume"].get<double>();
					Format.MaxVolume = itrobj["maxvolume"].get<double>();

					types.push_back(Format);
				}
				Format.CreateFlag = true;
			}
		}
		return true;
	}

	/// <summary>
	/// プリロード対象のファイル情報をすべて読み込むために生まれてきた関数
	/// </summary>
	/// <param name="preloadFiles"></param>
	bool AudioFormatData::LoadAudioPreloadFormatData(std::vector<AudioCue>& preloadFiles)
	{
		// ファイルの取得
		std::string Path = CreateFormatPDataPath();
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
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			AudioCue _resourcedata;
			// 同一名の物を検索
			picojson::object obj = cueitr.second.get<picojson::object>();

			_resourcedata.CueID = (uint16_t)obj["id"].get<double>();
			_resourcedata.CueName = obj["name"].get < std::string >();
			_resourcedata.VolType = (VOLUMETYPE)((int)obj["volumetype"].get<double>());
			_resourcedata.Loopflag = obj["loopflag"].get<bool>();
			_resourcedata.Filepath = CreateAudioDataPath();
			_resourcedata.StreamType = (AudioLoadType)((int)obj["loadtype"].get<double>());

			picojson::array& effectarray = obj["effects"].get<picojson::array>();
			for (auto effectitr : effectarray)
			{
				EffectState state;
				state.UseEffect = (EFFECTSNUM)((int)effectitr.get<picojson::object>()["effect"].get<double>());
				state.UseElement = effectitr.get<picojson::object>()["element"].get<std::string>();
				_resourcedata.CueEffect.push_back(state);
			}

			picojson::array& soundinfoarray = obj["soundinfo"].get<picojson::array>();
			for (auto infoitr : soundinfoarray)
			{
				SoundType sT;
				picojson::object itrobj = infoitr.get<picojson::object>();

				sT.AudioID = (uint16_t)itrobj["id"].get<double>();
				sT.AudioName = itrobj["name"].get<std::string>();
				sT.Cue = itrobj["cue"].get<std::string>();
				sT.MaterialObj = itrobj["material"].get<std::string>();
				sT.RIFFType = (RIFFType)((int)itrobj["riff"].get<double>());
				sT.DefaultVolume = itrobj["defaultvolume"].get<double>();
				sT.MaxVolume = itrobj["maxvolume"].get<double>(); 
				sT.CreateFlag = true;

				// 取得した情報を取得
				_resourcedata.AudioInfo.push_back(sT);

			}
			preloadFiles.push_back(_resourcedata);
		}
		return true;
	}

	bool AudioFormatData::LoadEffectData(CHORUS_INFO& info, std::string effectelementpath)
	{

		std::string Path = CreateEffectDataPath(effectelementpath);

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "CHORUS")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();
				
				varobj = obj["waverotm"].get<picojson::object>();
				info.MaxWaveRotm = (uint16_t)varobj["MAX"].get<double>();
				info.MinWaveRotm = (uint16_t)varobj["MIN"].get<double>();

				varobj = obj["phase"].get<picojson::object>();
				info.MaxPhase = (uint16_t)varobj["MAX"].get<double>();
				info.MinPhase = (uint16_t)varobj["MIN"].get<double>();

				varobj = obj["rate"].get<picojson::object>();
				info.MaxRate = varobj["MAX"].get<double>();
				info.MinRate = varobj["MIN"].get<double>();

				varobj = obj["depth"].get<picojson::object>();
				info.MaxDepth = varobj["MAX"].get<double>();
				info.MinDepth = varobj["MIN"].get<double>();

				varobj = obj["feedback"].get<picojson::object>();
				info.MaxFeedback = varobj["MAX"].get<double>();
				info.MinFeedback = varobj["MIN"].get<double>();

				varobj = obj["delay"].get<picojson::object>();
				info.MaxDelay = varobj["MAX"].get<double>();
				info.MinDelay = varobj["MIN"].get<double>();
			}
		}

		return true;

	}

	bool AudioFormatData::LoadEffectData(DISTORTION_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "DISTORTION")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["edge"].get<picojson::object>();
				info.MaxEdge = varobj["MAX"].get<double>();
				info.MinEdge = varobj["MIN"].get<double>();

				varobj = obj["gain"].get<picojson::object>();
				info.MaxGain = varobj["MAX"].get<double>();
				info.MinGain = varobj["MIN"].get<double>();

				varobj = obj["lowpasscutoff"].get<picojson::object>();
				info.MaxLowpassCutOff = varobj["MAX"].get<double>();
				info.MinLowpassCutOff = varobj["MIN"].get<double>();

				varobj = obj["eqcenter"].get<picojson::object>();
				info.MaxEQCenter = varobj["MAX"].get<double>();
				info.MinEQCenter = varobj["MIN"].get<double>();

				varobj = obj["wqbandwidth"].get<picojson::object>();
				info.MaxEQBandWidth = varobj["MAX"].get<double>();
				info.MinEQBandWidth = varobj["MIN"].get<double>();
			}
		}
		return true;
	}


	bool AudioFormatData::LoadEffectData(ECHO_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "ECHO")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["delay"].get<picojson::object>();
				info.MaxDelay = varobj["MAX"].get<double>();
				info.MinDelay = varobj["MIN"].get<double>();

				varobj = obj["lrdelay"].get<picojson::object>();
				info.MaxLRDelay = varobj["MAX"].get<double>();
				info.MinLRDelay = varobj["MIN"].get<double>();

				varobj = obj["damping"].get<picojson::object>();
				info.MaxDamping = varobj["MAX"].get<double>();
				info.MinDamping = varobj["MIN"].get<double>();

				varobj = obj["feedback"].get<picojson::object>();
				info.MaxFeedBack = varobj["MAX"].get<double>();
				info.MinFeedBack = varobj["MIN"].get<double>();

				varobj = obj["spread"].get<picojson::object>();
				info.MaxSPRead = varobj["MAX"].get<double>();
				info.MinSPRead = varobj["MIN"].get<double>();
			}
		}
		return true;
	}

	bool AudioFormatData::LoadEffectData(EQ_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "EQ")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["lowgain"].get<picojson::object>();
				info.MaxLowGain = varobj["MAX"].get<double>();
				info.MinLowGain = varobj["MIN"].get<double>();

				varobj = obj["lowcutoff"].get<picojson::object>();
				info.MaxLowCutOff = varobj["MAX"].get<double>();
				info.MinLowCutOff = varobj["MIN"].get<double>();

				varobj = obj["mid1gain"].get<picojson::object>();
				info.MaxMidGain = varobj["MAX"].get<double>();
				info.MinMidGain = varobj["MIN"].get<double>();

				varobj = obj["mid1center"].get<picojson::object>();
				info.MaxMidCenter = varobj["MAX"].get<double>();
				info.MinMidCenter = varobj["MIN"].get<double>();

				varobj = obj["mid1width"].get<picojson::object>();
				info.MaxMidWidth = varobj["MAX"].get<double>();
				info.MinMidWidth = varobj["MIN"].get<double>();

				varobj = obj["mid2gain"].get<picojson::object>();
				info.MaxMid2Gain = varobj["MAX"].get<double>();
				info.MinMid2Gain = varobj["MIN"].get<double>();

				varobj = obj["mid2center"].get<picojson::object>();
				info.MaxMid2Center = varobj["MAX"].get<double>();
				info.MinMid2Center = varobj["MIN"].get<double>();

				varobj = obj["mid2width"].get<picojson::object>();
				info.MaxMid2Width = varobj["MAX"].get<double>();
				info.MinMid2Width = varobj["MIN"].get<double>();

				varobj = obj["highgain"].get<picojson::object>();
				info.MaxHighGain = varobj["MAX"].get<double>();
				info.MinHighGain = varobj["MIN"].get<double>();

				varobj = obj["highcutoff"].get<picojson::object>();
				info.MaxHighCutOff = varobj["MAX"].get<double>();
				info.MinHighCutOff = varobj["MIN"].get<double>();

			}
		}
		return true;
	}

	bool AudioFormatData::LoadEffectData(FLANGER_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "FLANGER")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["waveform"].get<picojson::object>();
				info.MaxWaveForm = (uint16_t)varobj["MAX"].get<double>();
				info.MinWaveForm = (uint16_t)varobj["MIN"].get<double>();

				varobj = obj["phase"].get<picojson::object>();
				info.MaxPhase = (uint16_t)varobj["MAX"].get<double>();
				info.MinPhase = (uint16_t)varobj["MIN"].get<double>();

				varobj = obj["rate"].get<picojson::object>();
				info.MaxRate = varobj["MAX"].get<double>();
				info.MinRate = varobj["MIN"].get<double>();

				varobj = obj["depth"].get<picojson::object>();
				info.MaxDepth = varobj["MAX"].get<double>();
				info.MinDepth = varobj["MIN"].get<double>();

				varobj = obj["feedback"].get<picojson::object>();
				info.MaxFeedback = varobj["MAX"].get<double>();
				info.MinFeedback = varobj["MIN"].get<double>();

				varobj = obj["delay"].get<picojson::object>();
				info.MaxDelay = varobj["MAX"].get<double>();
				info.MinDelay = varobj["MIN"].get<double>();
			}
		}
		return true;
	}

	bool AudioFormatData::LoadEffectData(FQ_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "FQ")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["frequency"].get<picojson::object>();
				info.MaxFrequency = (uint16_t)varobj["MAX"].get<double>();
				info.MinFrequency = (uint16_t)varobj["MIN"].get<double>();

				varobj = obj["leftdirection"].get<picojson::object>();
				info.MaxLeftDirection = (uint16_t)varobj["MAX"].get<double>();
				info.MinLeftDirection = (uint16_t)varobj["MIN"].get<double>();

				varobj = obj["rightdirection"].get<picojson::object>();
				info.MaxRightDirection = (uint16_t)varobj["MAX"].get<double>();
				info.MinRightDirection = (uint16_t)varobj["MIN"].get<double>();
			}
		}
	}

	bool AudioFormatData::LoadEffectData(PITCH_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "PATCH")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["coarsetune"].get<picojson::object>();
				info.MaxCoarseTune = (uint16_t)varobj["MAX"].get<double>();
				info.MinCoarseTune = (uint16_t)varobj["MIN"].get<double>();

				varobj = obj["finetune"].get<picojson::object>();
				info.MaxFineTune = (uint16_t)varobj["MAX"].get<double>();
				info.MinFineTune = (uint16_t)varobj["MIN"].get<double>();
			}
		}
	}

	bool AudioFormatData::LoadEffectData(REVERB_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "REVERB")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["density"].get<picojson::object>();
				info.MaxDensity = varobj["MAX"].get<double>();
				info.MinDensity = varobj["MIN"].get<double>();

				varobj = obj["diffusion"].get<picojson::object>();
				info.MaxDiffusion = varobj["MAX"].get<double>();
				info.MinDiffusion = varobj["MIN"].get<double>();

				varobj = obj["gain"].get<picojson::object>();
				info.MaxGain = varobj["MAX"].get<double>();
				info.MinGain = varobj["MIN"].get<double>();

				varobj = obj["gainhf"].get<picojson::object>();
				info.MaxGainHF = varobj["MAX"].get<double>();
				info.MinGainHF = varobj["MIN"].get<double>();

				varobj = obj["decaytime"].get<picojson::object>();
				info.MaxDecayTime = varobj["MAX"].get<double>();
				info.MinDecayTime = varobj["MIN"].get<double>();

				varobj = obj["decayhfratio"].get<picojson::object>();
				info.MaxDecayHFRatio = varobj["MAX"].get<double>();
				info.MinDecayHFRatio = varobj["MIN"].get<double>();

				varobj = obj["reflectiongain"].get<picojson::object>();
				info.MaxReflectionsGain = varobj["MAX"].get<double>();
				info.MinReflectionsGain = varobj["MIN"].get<double>();

				varobj = obj["reflectiondelay"].get<picojson::object>();
				info.MaxReflectionsDelay = varobj["MAX"].get<double>();
				info.MinReflectionsDelay = varobj["MIN"].get<double>();
				
				varobj = obj["lategain"].get<picojson::object>();
				info.MaxLateGain = varobj["MAX"].get<double>();
				info.MinLateGain = varobj["MIN"].get<double>();

				varobj = obj["latedelay"].get<picojson::object>();
				info.MaxLateDelay = varobj["MAX"].get<double>();
				info.MinLateDelay = varobj["MIN"].get<double>();

				varobj = obj["roomrolloff"].get<picojson::object>();
				info.MaxRoomRollOff = varobj["MAX"].get<double>();
				info.MinRoomRollOff = varobj["MIN"].get<double>();

				varobj = obj["airgainhf"].get<picojson::object>();
				info.MaxAirGainHF = varobj["MAX"].get<double>();
				info.MinAirGainHF = varobj["MIN"].get<double>();

				info.AIR_HFLIMIT = obj["airhflimit"].get<bool>();
			}
		}
	}

	bool AudioFormatData::LoadEffectData(WAH_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "WAH")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["attacktime"].get<picojson::object>();
				info.MaxAttackTime = varobj["MAX"].get<double>();
				info.MinAttackTime = varobj["MIN"].get<double>();

				varobj = obj["releasetime"].get<picojson::object>();
				info.MaxRleaseTime = varobj["MAX"].get<double>();
				info.MinRleaseTime = varobj["MIN"].get<double>();

				varobj = obj["resonance"].get<picojson::object>();
				info.MaxResonace = varobj["MAX"].get<double>();
				info.MinResonace = varobj["MIN"].get<double>();

				varobj = obj["peakgain"].get<picojson::object>();
				info.MaxPeakGain = varobj["MAX"].get<double>();
				info.MinPeakGain = varobj["MIN"].get<double>();

			}
		}
	}

	bool AudioFormatData::LoadEffectData(CONE_INFO& info, std::string effectelementpath)
	{
		std::string Path = CreateEffectDataPath(effectelementpath);	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}

		// エフェクトのデータを抜け出す
		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			// 同一名の物を検索
			if (cueitr.first == "CORN")
			{
				picojson::object varobj; // 色々なものを書くのするよう
				picojson::object obj = cueitr.second.get<picojson::object>();

				info.CorrectionValue = obj["correctionvalue"].get<double>();

				varobj = obj["attacktime"].get<picojson::object>();
				info.ConeOuterGain = varobj["coneoutergain"].get<double>();
				info.InnerAngle = varobj["innerangle"].get<double>();
				info.OuterAngle = varobj["outerangle"].get<double>();

			}
		}
	}

	bool AudioFormatData::LoadEffefctPramData(std::list<EffectElementPram*> pram)
	{
		std::string Path = CreateEffectDataPath("EffectElementPram");	// ファイルパス設定

		std::ifstream ifs(Path.c_str(), std::ios::in); // jsonファイルをオープン

		if (ifs.fail())
			return false;

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		// jsonデータの解析
		picojson::value Val;
		const std::string err = picojson::parse(Val, json);
		if (err.empty() == false)
		{
			return false;
		}
		
		uint16_t id;
		std::string name;
		double initvalue = 0;
		double maxvalue = 0;
		double minvalue = 0;

		picojson::object obj = Val.get<picojson::object>();
		for (auto cueitr : obj)
		{
			picojson::object varobj; // 色々なものを書くのするよう
			picojson::object obj = cueitr.second.get<picojson::object>();

			id = obj["id"].get<double>();
			name = obj["name"].get<std::string>();
			name = obj["default"].get<double>();
			name = obj["max"].get<double>();
			name = obj["min"].get<double>();

			pram.push_back(new EffectElementPram(id,name,initvalue,maxvalue,minvalue));
		}

		return true;


	}

	void AudioFormatData::SetAudioPath(std::string path)
	{
		ExeDirectory = path;
		DataPath = "/Data/";
	}

	std::string AudioFormatData::CreateFormatSDataPath()
	{
		return ExeDirectory + DataPath + "json/htAudioStreamInfo.json";
	}

	std::string AudioFormatData::CreateFormatPDataPath()
	{
		return ExeDirectory + DataPath + "json/htAudioPreloadInfo .json";
	}

	std::string AudioFormatData::CreateEffectDataPath(std::string dataname)
	{
		return ExeDirectory + DataPath + "json/" + dataname +".json";
	}

	std::string AudioFormatData::CreateAudioDataPath()
	{
		return ExeDirectory + DataPath + "Audio/";
	}

}