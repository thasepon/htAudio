#pragma once

#include<string>
#include<map>
#include <functional>
#include <utility>
#include<iostream>

namespace htAudio {

	struct ElementInfo
	{
		int Id;
		std::string Name;
	};

	class AudioElement
	{
	public:
		AudioElement();
		~AudioElement();

		void CreateElement(std::string name);
		void DeleteElement(std::string name);
		void DeleteElement(int id);

	private:
		std::map<int,ElementInfo> ElementMap;
		int ElementidCnt = 0;	// ÉÜÉjÅ[ÉNID

	};

}