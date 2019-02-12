#pragma once

#include<vector>
#include<string>
#include<map>


namespace htAudio {

	struct GropuInfo
	{
		unsigned short GroupId;
		std::string GropName;
		std::vector<int> SourceId;
	};

	/// <summary>
	/// �I�[�f�B�I�̃O���[�v���ʂ����邽�߂̃N���X
	/// </summary>
	class AudioGroup
	{
	public:
		AudioGroup();
		~AudioGroup();

		std::map<std::string, GropuInfo> GetGropulist();

		void CreateGropu(std::string name);
		void DeleteGropu(std::string name);

	private:
		std::map<std::string,GropuInfo> AudioGropulist;
		unsigned short GroupIdCnter;

	};

}