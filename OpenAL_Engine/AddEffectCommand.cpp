#include "AddEffectCommand.h"

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

namespace htAudio
{
	AddEffectCommand::~AddEffectCommand()
	{

	}

	AudioEffects* AddEffectCommand::CreateEffect(int sourceID,int effect)
	{
		// エフェクトの生成と返信
		AudioEffects* effectPtr;

		// 指定エフェクトの生成と返信
		switch (effect)
		{
		case REVERB:
			effectPtr = new ReverbEffects(sourceID);
			break;

		case CHORUS:
			effectPtr = new ChorusEffect(sourceID);
			break;

		case DISTORTION:
			effectPtr = new DistortionEffect(sourceID);
			break;

		case ECHO:
			effectPtr = new EchoEffect(sourceID);
			break;

		case FLANGER:
			effectPtr = new FlangerEffect(sourceID);
			break;

		case FQ:
			effectPtr = new FQEffect(sourceID);
			break;

		case PITCH:
			effectPtr = new PitchEffect(sourceID);
			break;

		case WAH:
			effectPtr = new WahEffect(sourceID);
			break;

		case EQ:
			effectPtr = new EQEffect(sourceID);
			break;

		case I3DAUDIO:
			effectPtr = new I3DAudio(sourceID);
			break;

		default:
			effectPtr = nullptr;
			break;
		}

		return effectPtr;


	}

}