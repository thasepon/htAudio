#pragma once

#include<string>
#include<map>
#include"AudioDecoder.h"

namespace htAudio
{
	// ���\�[�X�g���܂킵�ɕK�v�ȃf�[�^
	struct ResourceData
	{
		AUDIOFILEFORMAT fmt;
		void* DataBuffer;
	};

	/// <summary>
	/// wav��ogg�̃I�[�f�B�I�̊Ǘ�������N���X
	/// �������o�R���ă��\�[�X���擾����
	/// </summary>
	class AudioReSource
	{
	public:
		AudioReSource();
		~AudioReSource();

		void PreLoad(std::string name);	// �������ɂ̂��čė��p���܂�
		void PreLoad(int Id);			// �������ɂ̂��čė��p���܂�
		void StreamLoad(std::string);	// �������ɕ������Ă̂��čĐ���͉�����܂�
		void StreamLoad(int Id);	// �������ɕ������Ă̂��čĐ���͉�����܂�
		
		void ReleaseResource();	// ���݃������Ɋm�ۂ��Ă��鉹����������܂�
		
	private:
		// �ǂ݂��񂾃t�@�C���̕ۑ��pmap
		ResourceData* AudioresourceMap;

	};

}