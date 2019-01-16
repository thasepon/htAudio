#include "AudioElement.h"

namespace htAudio {

	AudioElement::AudioElement()
	{
		ElementMap.clear();
	}

	AudioElement::~AudioElement()
	{
		ElementMap.clear();
	}

	/// <summary>
	/// 新規エレメントの作成
	/// </summary>
	/// <param name="name"></param>
	void AudioElement::CreateElement(std::string name)
	{
		ElementInfo element;
		element.Name = name;
		ElementMap.insert( std::make_pair(ElementidCnt, element));
	}

	/// <summary>
	/// エレメントの削除
	/// </summary>
	/// <param name="name"></param>
	void AudioElement::DeleteElement(std::string name)
	{
		if (ElementMap.empty())
		{
			return;
		}

		for (auto& itr : ElementMap)
		{
			if (itr.second.Name == name)
			{
				ElementMap.erase(itr.first);
			}
		}

	}

	/// <summary>
	/// エレメントの削除
	/// </summary>
	/// <param name="id"></param>
	void AudioElement::DeleteElement(int id)
	{
		if (ElementMap.empty())
		{
			return;
		}

		if (ElementMap.count(id))
		{
			ElementMap.erase(id);
		}
	}

}