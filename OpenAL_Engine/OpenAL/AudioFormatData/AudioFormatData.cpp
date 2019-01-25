#include "AudioFormatData.h"
#include <codecvt>

namespace htAudio {

	using namespace pugi;

	AudioFormatData::AudioFormatData()
	{
	}


	AudioFormatData::~AudioFormatData()
	{

	}

	std::vector<SoundType> AudioFormatData::GetAudioFormatData(std::string filepath, std::string Soundname)
	{
		
		std::vector<SoundType> Formats;
		SoundType Format;
		xml_document doc;
		xml_parse_result result;
		
		// ファイルパスの指定(仮)
		filepath += "\\Xml\\SoundList.xml";

		// ドキュメントファイルの読み込み
		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (result == false)
		{
			Format.CreateFlag = result;
			return Formats;
		}

		xml_node tools = doc.child("SoundList");

		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			// 指定したサウンドの階層
			auto xmlname = tool.attribute("Name").value();
			if (xmlname == Soundname)
			{
				// サウンド情報の設定
				for (xml_node soundinfo = tool.child("SoundInfo"); soundinfo; soundinfo = soundinfo.next_sibling())
				{

					Format.AudioID		= (int)tool.attribute("ID").hash_value();
					Format.AudioName	= soundinfo.child_value("AudioName");
					Format.b3DAudio		= atoi(tool.child("SoundType").child_value("SurroundFlag"));
					Format.Cue			= tool.child("SoundType").child_value("Cue");
					Format.SubGroup		= tool.child("SoundType").child_value("SubGroup");
					Format.MaterialObj	= soundinfo.child_value("Material");
					Format.Loopflag		= atoi(tool.child("SoundType").child_value("Loop"));
					Format.StreamType	= (AudioLoadType)atoi(tool.child("SoundType").child_value("StreamType"));
					Format.RIFFType		= (RIFFType)atoi(soundinfo.child_value("RIFFType"));
					Format.LowVolume	= atof(soundinfo.child_value("LowVolume"));
					Format.DefaultVolume= atof(soundinfo.child_value("DefaultVolume"));
					Format.MaxVolume	= atof(soundinfo.child_value("MaxVolume"));
					Format.CreateFlag	= true;

					Formats.push_back(Format);
				}

			}
		}
		return Formats;
	}


	std::vector<SoundType> AudioFormatData::GetAudioFormatData(std::string filepath, int id)
	{
		std::vector<SoundType> Formats;
		SoundType Format;
		xml_document doc;
		xml_parse_result result;

		Format.CreateFlag = false;

		filepath += "\\Xml\\SoundList.xml";

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (result == false)
		{
			Format.CreateFlag = false;
			return Formats;
		}

		xml_node tools = doc.child("SoundList");

		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			// 指定したサウンドの階層
			if (tool.attribute("Id").hash_value() == id)
			{
				// サウンド情報の設定
				for (xml_node soundinfo = tool.child("SoundInfo"); soundinfo; soundinfo = soundinfo.next_sibling())
				{

					Format.AudioID = (int)tool.attribute("ID").hash_value();
					Format.AudioName = soundinfo.child_value("AudioName");
					Format.b3DAudio = atoi(tool.child("SoundType").child_value("SurroundFlag"));
					Format.Cue = tool.child("SoundType").child_value("Cue");
					Format.SubGroup = tool.child("SoundType").child_value("SubGroup");
					Format.MaterialObj = soundinfo.child_value("Material");
					Format.Loopflag = atoi(tool.child("SoundType").child_value("Loop"));
					Format.StreamType = (AudioLoadType)atoi(tool.child("SoundType").child_value("StreamType"));
					Format.RIFFType = (RIFFType)atoi(soundinfo.child_value("RIFFType"));
					Format.LowVolume = atof(soundinfo.child_value("LowVolume"));
					Format.DefaultVolume = atof(soundinfo.child_value("DefaultVolume"));
					Format.MaxVolume = atof(soundinfo.child_value("MaxVolume"));
					Format.CreateFlag = true;

					Formats.push_back(Format);
				}
			}
		}

		Format.CreateFlag = true;
		return Formats;

	}

	/*void AudioFormatData::WriteAudioFormatData(std::string filepath, SoundType registinfo)
	{
		using namespace pugi;

		xml_document doc;

		xml_parse_result result;

		filepath += "\\Xml\\SoundList.xml";

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (result == false)
		{
			return;
		}

		xml_node tools = doc.child("SoundList");
		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			if (tool.attribute("Id").hash_value() == registinfo.DataID)
			{
				if (registinfo.b3DAudio == 0)
					continue;
				xml_node soundinfo = tool.child("SurroundInfo");
				char buf[24];

				snprintf(buf, 24, "%f", registinfo.Sorrundinfo.OuterGain);
				soundinfo.child("OuterGain").set_value(buf);

				snprintf(buf, 24, "%f", registinfo.Sorrundinfo.OuterAngle);
				soundinfo.child("OuterAngle").set_value(buf);

				snprintf(buf, 24, "%f", registinfo.Sorrundinfo.innerAngle);
				soundinfo.child("InnerAngle").set_value(buf);
			}
		}

	}*/

	bool AudioFormatData::ReadListenerState(ConeState& state, std::string filepath)
	{
		using namespace pugi;
		xml_document doc;
		xml_parse_result result;

		filepath += "\\Xml\\ListenerState.xml";

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (!result)
		{
			return false;
		}

		xml_node tools = doc.child("ListenerState");
		xml_node tool = tools.child("State");

		state.ConeOuterGain  = (float)atof(tool.child_value("ConeQuterGain"));
		state.InnerAngle = (float)atof(tool.child_value("ConeInnerAngle"));
		state.OuterAngle = (float)atof(tool.child_value("ConeOuterAngle"));

		return true;
	}

	//bool AudioFormatData::WriteListenerState(ListenerStates state, std::string filepath)
	//{
	//	using namespace pugi;
	//	xml_document doc;
	//	xml_parse_result result;

	//	filepath += "\\Xml\\ListenerState.xml";

	//	result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

	//	if (!result)
	//	{
	//		return false;
	//	}

	//	xml_node tools = doc.child("ListenerState");
	//	xml_node tool = tools.child("State");

	//	// 登録用の変数配列
	//	char buf[24];

	//	snprintf(buf,24,"%f",state.OuterGain);
	//	tool.child("ConeQuterGain").set_value(buf);

	//	snprintf(buf, 24, "%f", state.InnerAngle);
	//	tool.child("ConeInnerAngle").set_value(buf);

	//	snprintf(buf, 24, "%f", state.OuterAngle);
	//	tool.child("ConeOuterAngle").set_value(buf);
	//	
	//	return true;
	//}

}