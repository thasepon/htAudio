#pragma once

#include<string>
#include"AudioDecoder.h"
#include<vector>

namespace htAudio
{
	/// <summary>
	/// wav��ogg�̃I�[�f�B�I�̊Ǘ�������N���X
	/// �������o�R���ă��\�[�X���擾����
	/// </summary>
	class AudioReSource
	{
	public:
		AudioReSource();
		~AudioReSource();
		void ReadPreLoadAudio();	// �v�����[�h���鉹������C�ɓǂݍ���Őݒ肷��
		void GetAudioBuffer(std::string name);			// �I�[�f�B�I�o�b�t�@���擾����
		void GetAudioBuffer(int Id);			// �I�[�f�B�I�o�b�t�@���擾����
		void ReleaseResource();			// ���݃������Ɋm�ۂ��Ă��鉹����������܂�
		
	private:
		// �ǂ݂��񂾃t�@�C���̕ۑ��pmap
		std::vector<ResourceData> Audioresourcelist;
		
		std::vector<int16_t> preloadBuf;

	};

}