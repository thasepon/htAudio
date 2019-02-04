#pragma once

#include<string>
#include<list>
#include"EffectElementPram.h"
#include"AudioData.h"
#include"AudioEffects.h"

namespace htAudio
{
	class EffectManager
	{
	public:
		EffectManager();
		~EffectManager();

		// �w��X�s�[�J�[�ɃG�t�F�N�g��K��
		static void AddEffectToSpeaker(std::vector<AudioEffects*> effectptr,AudioCue effectinfo, uint16_t sourceid);
		
		// ElementPram�����������ɑS������
		void LoadExternalFileElementPram();
		
		// EffectParameter�̎擾
		EffectElementPram* GetElementPram(std::string _elementpramname);


	private:
		std::list<EffectElementPram*> ParameterList; //�|�C���^�����L���Đ��l�����L���܂�

	};
}