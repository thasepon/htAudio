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
		virtual AudioEffects* Execute(int sourceID,int effect) { return CreateEffect(sourceID,effect); }

	private:
		AudioEffects* CreateEffect(int sourceID, int effect);	// エフェクト追加関数
	};
}