#pragma once

#include<string>
#include"AudioDecoder.h"
#include<vector>
#include<map>
#include<memory>

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
		void ReadPreLoadAudio();							// �v�����[�h���鉹������C�ɓǂݍ���Őݒ肷��
		void GetAudioBuffer(SoundType Target, long* buf);	// �I�[�f�B�I�o�b�t�@���擾����
		void ReleaseResource();								// ���݃������Ɋm�ۂ��Ă��鉹����������܂�
		
		// --- Fotmat�n
		void ReadCueFormatData();							// �쐬����json�f�[�^��ǂݍ���ŕێ�����
		AudioCue GetFormatData(int CueId);					// �ǂݍ���Cue�f�[�^���擾����
		AudioCue GetFormatData(std::string CueName);		// �ǂݍ���Cue�f�[�^���擾����
		void ReleaseFormatData();							// �ǂݍ���json�f�[�^���폜����

	private:
		std::vector<AudioCue> Audioresourcelist;			// �S�t�@�C���̃t�@�C�������擾
		std::map<int,long*> BufferMap;						// PreloadBuffer���̕ۑ� <AuidoID,Buffer>
	};

}