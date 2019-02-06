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
	/// �p�����[�^�[�̎擾
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

		// ������������Ȃ������ꍇ�͊O���t�@�C�������������Ă���ł�������Ȃ��ꍇ��nullptr��Ԃ�
		return nullptr;
		
	}

}