#pragma once

#include<vector>
#include"AudioEffects.h"
#include"AudioData.h"
namespace htAudio
{
	class AddEffectCommand
	{
	public:
		~AddEffectCommand();
		virtual AudioEffects* Execute(int sourceID, int effectid, std::string useelement) { return CreateEffect(sourceID,effectid,useelement); }

	private:
		AudioEffects* CreateEffect(int sourceID, int effectid, std::string useelement);	// �G�t�F�N�g�ǉ��֐�
	};
}