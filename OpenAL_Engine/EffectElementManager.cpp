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

		// もしも見つからなかった場合は外部ファイル検索をかけてそれでも見つからない場合はnullptrを返す
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