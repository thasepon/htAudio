#include "AddEffectCommand.h"

#include<string>

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

#include"Singleton.h"
#include"AudioManager.h"

namespace htAudio
{
	AddEffectCommand::~AddEffectCommand()
	{

	}

	AudioEffects* AddEffectCommand::CreateEffect(int sourceID,int effectid ,std::string useelement)
	{
		// エフェクトの生成と返信
		AudioEffects* effectPtr;
		std::string elementpram;
		EffectElementPram* pram;

		// 指定エフェクトの生成と返信
		switch (effectid)
		{
		case REVERB:
			effectPtr = new ReverbEffects(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case CHORUS:
			effectPtr = new ChorusEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case DISTORTION:
			effectPtr = new DistortionEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case ECHO:
			effectPtr = new EchoEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case FLANGER:
			effectPtr = new FlangerEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case FQ:
			effectPtr = new FQEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case PITCH:
			effectPtr = new PitchEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case WAH:
			effectPtr = new WahEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case EQ:
			effectPtr = new EQEffect(sourceID, useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		case I3DAUDIO:
			//effectPtr = new I3DAudio(sourceID, useelement);
			break;

		case CONE:
			effectPtr = new Cone(sourceID,useelement);
			elementpram = effectPtr->GetEffectPramName();
			pram = Singleton<AudioManager>::get_Instance()->GetEffectElementPtr()->GetElementPram(elementpram);
			effectPtr->SetEffectParametr(pram);
			break;

		default:
			effectPtr = nullptr;
			break;
		}
		return effectPtr;
	}

}