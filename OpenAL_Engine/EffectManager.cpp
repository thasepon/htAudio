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

	void EffectManager::AddEffectToSpeaker(std::vector<AudioEffects*> effectptr, AudioCue effectinfo,uint16_t sourceid)
	{
		for (auto itr : effectinfo.CueEffect)
		{
			switch (itr.UseEffect)
			{
			case REVERB:
				effectptr.push_back(new ReverbEffects(sourceid, itr.UseElement));
				break;

			case CHORUS:
				effectptr.push_back(new ChorusEffect(sourceid, itr.UseElement));
				break;

			case DISTORTION:
				effectptr.push_back(new DistortionEffect(sourceid, itr.UseElement));
				break;

			case ECHO:
				effectptr.push_back(new EchoEffect(sourceid,itr.UseElement));
				break;

			case FLANGER:
				effectptr.push_back(new FlangerEffect(sourceid, itr.UseElement));
				break;

			case FQ:
				effectptr.push_back(new FQEffect(sourceid, itr.UseElement));
				break;

			case PITCH:
				effectptr.push_back(new PitchEffect(sourceid, itr.UseElement));
				break;

			case WAH:
				effectptr.push_back(new WahEffect(sourceid, itr.UseElement));
				break;

			case EQ:
				effectptr.push_back(new EQEffect(sourceid, itr.UseElement));
				break;
				
			case CONE:
				effectptr.push_back(new Cone(sourceid, itr.UseElement));
				break;

			default:
				break;
			}
		}
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