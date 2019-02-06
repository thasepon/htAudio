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

namespace htAudio
{
	AddEffectCommand::~AddEffectCommand()
	{

	}

	AudioEffects* AddEffectCommand::CreateEffect(int sourceID,int effectid ,std::string useelement)
	{
		// エフェクトの生成と返信
		AudioEffects* effectPtr;

		// 指定エフェクトの生成と返信
		switch (effectid)
		{
		case REVERB:
			effectPtr = new ReverbEffects(sourceID, useelement);
			effectPtr->SetEffectParametr();
			break;

		case CHORUS:
			effectPtr = new ChorusEffect(sourceID, useelement);
			break;

		case DISTORTION:
			effectPtr = new DistortionEffect(sourceID, useelement);
			break;

		case ECHO:
			effectPtr = new EchoEffect(sourceID, useelement);
			break;

		case FLANGER:
			effectPtr = new FlangerEffect(sourceID, useelement);
			break;

		case FQ:
			effectPtr = new FQEffect(sourceID, useelement);
			break;

		case PITCH:
			effectPtr = new PitchEffect(sourceID, useelement);
			break;

		case WAH:
			effectPtr = new WahEffect(sourceID, useelement);
			break;

		case EQ:
			effectPtr = new EQEffect(sourceID, useelement);
			break;

		case I3DAUDIO:
			//effectPtr = new I3DAudio(sourceID, useelement);
			break;

		case CONE:
			effectPtr = new Cone(sourceID,useelement);
			break;

		default:
			effectPtr = nullptr;
			break;
		}
		return effectPtr;
	}

}