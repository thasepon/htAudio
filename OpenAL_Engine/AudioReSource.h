#pragma once

#include<string>
#include"AudioDecoder.h"
#include<vector>
#include<map>

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

		// --- Buffer�n
		void ReadPreLoadAudio();									// �v�����[�h���鉹������C�ɓǂݍ���Őݒ肷��
		void GetAudioBuffer(SoundType Target,void* buf);			// �I�[�f�B�I�o�b�t�@���擾����
		void ReleaseResource();										// ���݃������Ɋm�ۂ��Ă��鉹����������܂�
		
		// --- Fotmat�n
		void ReadCueFormatData();	// �쐬����json�f�[�^��ǂݍ���ŕێ�����
		AudioCue GetFormatData(int CueId);		// �ǂݍ���Cue�f�[�^���擾����
		AudioCue GetFormatData(std::string CueName);		// �ǂݍ���Cue�f�[�^���擾����
		void ReleaseFormatData();	// �ǂݍ���json�f�[�^���폜����

	private:
		// �ǂ݂��񂾃t�@�C�����̕ۑ��pmap
		std::vector<AudioCue> Audioresourcelist;

		// Buffer���̕ۑ� <AuidoID,Buffer>
		std::map<int,int16_t*> BufferMap;

	};

}