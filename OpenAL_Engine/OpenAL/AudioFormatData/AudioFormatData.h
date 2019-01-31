#pragma once

#include<iostream>
#include<string>
#include<tchar.h>

#include"../../AudioData.h"

namespace htAudio
{
	/// <summary>
	/// �O���t�@�C���ɕۑ����Ă������ǂݍ��ޏ���
	/// </summary>
	class AudioFormatData
	{
	public:
		AudioFormatData();
		~AudioFormatData();

		static bool LoadAudioFormatData(AudioCue& cue,std::vector<SoundType>& types, std::string filepath, std::string Soundname);
		static bool LoadAudioFormatData(AudioCue& cue, std::vector<SoundType>& types, std::string filepath, int id);
		
		// �e��G�t�F�N�g�̃f�[�^���Ăэ���
		static bool LoadEffectData();

	private:


	};

}