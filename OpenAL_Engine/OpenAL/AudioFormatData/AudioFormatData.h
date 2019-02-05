#pragma once

#include<iostream>
#include<string>
#include<tchar.h>

#include"../../AudioData.h"
#include"../../AudioEffects.h"
#include"../../EffectElementPram.h"

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

		static bool LoadAudioFormatData(AudioCue& cue,std::vector<SoundType>& types, std::string Soundname);
		static bool LoadAudioFormatData(AudioCue& cue,std::vector<SoundType>& types, int id);
		
		// �e��G�t�F�N�g�̃f�[�^���Ăэ�
		// �G�t�F�N�g�̕������I�[�o�[���C�h���Ȃ��ƃ_���ȋC������
		static bool LoadEffectData(CHORUS_INFO& info,std::string effectelementpath);
		static bool LoadEffectData(DISTORTION_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(ECHO_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(EQ_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(FLANGER_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(FQ_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(PITCH_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(REVERB_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(WAH_INFO& info, std::string effectelementpath);
		static bool LoadEffectData(CONE_INFO& info ,std::string effectelementpath);

		static bool LoadEffefctPramData(std::list<EffectElementPram*> pram);

	private:
		static std::string CreateFormatDataPath();
		static std::string CreateEffectDataPath(std::string dataname);
	};
}