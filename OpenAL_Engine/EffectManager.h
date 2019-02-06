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

		// ElementPram�����������ɑS�擾
		void LoadExternalFileElementPram();

		// EffectParameter�̎擾
		EffectElementPram* GetElementPram(std::string _elementpramname);

	private:
		std::list<EffectElementPram*> ParameterList; //�|�C���^�����L���Đ��l�����L���܂�

	};
}