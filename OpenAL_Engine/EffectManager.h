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

		// 指定スピーカーにエフェクトを適応
		static void AddEffectToSpeaker(std::vector<AudioEffects*> effectptr,AudioCue effectinfo, uint16_t sourceid);
		
		// ElementPramを初期化時に全取得
		void LoadExternalFileElementPram();
		
		// EffectParameterの取得
		EffectElementPram* GetElementPram(std::string _elementpramname);


	private:
		std::list<EffectElementPram*> ParameterList; //ポインタを共有して数値を共有します

	};
}