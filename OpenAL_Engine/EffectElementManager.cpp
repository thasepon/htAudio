#include "EffectElementManager.h"

namespace htAudio
{

	EffectElementManager::EffectElementManager()
	{
	}


	EffectElementManager::~EffectElementManager()
	{
	}


	EffectElementPram* EffectElementManager::GetElementPram(std::string _elementpramname)
	{
		if (ParameterList.empty())
			return nullptr;

		for (auto itr : ParameterList)
		{
			if (itr->GetElementName == _elementpramname)
				return itr;
		}

		// ������������Ȃ������ꍇ�͊O���t�@�C�������������Ă���ł�������Ȃ��ꍇ��nullptr��Ԃ�
		return SerchExternalFileElementPram();
		
	}

	EffectElementPram* EffectElementManager::SerchExternalFileElementPram()
	{



		return CreateElementPram();
	}

	EffectElementPram* EffectElementManager::CreateElementPram()
	{

	}

}