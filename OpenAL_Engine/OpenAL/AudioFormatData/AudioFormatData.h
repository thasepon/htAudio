#pragma once

#include<iostream>
#include<string>
#include<tchar.h>

#include"../AudioListener/AudioListener.h"
#include<pugixml.hpp>

#pragma comment(lib, "pugixml.lib")

namespace htAudio
{
	/// <summary>
	/// xmlの読み込み
	/// </summary>
	/// 
	class AudioFormatData
	{
	public:
		AudioFormatData();
		~AudioFormatData();

		static SoundType GetAudioFormatData(std::string filepath, std::string Soundname);
		static SoundType GetAudioFormatData(std::string filepath, int id);
		static void WriteAudioFormatData(std::string filepath, SoundType registinfo);
		static bool ReadListenerState(ListenerStates* state, std::string filepath);
		static bool WriteListenerState(ListenerStates state, std::string filepath);

		//bool ReadSpeakerState(ListenerStates* state, std::string filepath);
		//bool WriteSpeakerState(ListenerStates state, std::string filepath);

	private:


	};

}