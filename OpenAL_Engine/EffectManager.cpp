#include "EffectManager.h"
#include"OpenAL\AudioFormatData\AudioFormatData.h"
#include"ReverbEffects.h"
#include"ChorusEffect.h"
#include"DistortionEffect.h"
#include"EchoEffect.h"
#include"FlangerEffect.h"
#include"FQEffect.h"
#include"PitchEffect.h"
#include"WahEffect.h"
#include"EQEffect.h"
#include"I3DAudio.h"
#include"Cone.h"

namespace htAudio
{
	EffectManager::EffectManager()
	{
		LoadExternalFileElementPram();
	}


	EffectManager::~EffectManager()
	{
	}

	/// <summary>
	/// パラメーターの取得
	/// </summary>
	void EffectManager::LoadExternalFileElementPram()
	{
		AudioFormatData::LoadEffefctPramData(ParameterList);
	}

	EffectElementPram* EffectManager::GetElementPram(std::string _elementpramname)
	{
		if (ParameterList.empty())
			return nullptr;

		for (auto itr : ParameterList)
		{
			if (itr->GetElementName() == _elementpramname)
				return itr;
		}

		// もしも見つからなかった場合は外部ファイル検索をかけてそれでも見つからない場合はnullptrを返す
		return nullptr;
		
	}

}