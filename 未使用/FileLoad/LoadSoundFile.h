#pragma once

#include<windows.h>
#include<vector>
#include<string>
#include<tchar.h>

#include<AL/al.h>
#include<AL/alc.h>

namespace htAudio
{

	struct Audio3D
	{
		double OuterGain;
		double OuterAngle;
		double innerAngle;
	};

	// �T�E���h���
	struct SoundInfo
	{
		int Id;
		std::string Extension;
		std::string SoundName;
		std::string MaterialObj;
		std::string Type;
		double LowVolume;
		double DefaultVolume;
		double MaxVolume;
	};

	// �T�E���h�̃^�C�v
	struct SoundType {
		int DataID;
		double b3DAudio;
		std::string Cue;
		std::string SubGroup;
		bool Loopflag;
		bool StreamType;
		std::vector<SoundInfo> Soundinfo;
		Audio3D Sorrundinfo;
		bool CreateFlag;
	};


	// �w�b�_�[���
	typedef struct {
		WORD  wFormatTag;
		WORD  nChannels;
		DWORD nSamplesPerSec;
		DWORD nAvgBytesPerSec;
		WORD  nBlockAlign;
		WORD  wBitsPerSample;
		WORD  cbSize;
	} AUDIOFORMAT;

	struct SoundResources
	{
		std::string PresetSoundName;// �T�E���h��
		AUDIOFORMAT Format;			// �w�b�_�[���
		SoundType Soundtype;		// XML���瓾�����
		int PlayTime;				// �Đ�����
		bool HasGotWaveFormat;		// �t�H�[�}�b�g�����擾�ς݂�
		bool LoopSound;				// ���[�v���

		std::size_t DataChunkSize;	// �f�[�^�o�b�t�@�T�C�Y
		std::size_t DataChunkSample;
		long firstSampleOffSet;

		// Buffer���
		std::size_t NextFirstSample = { 0 };
		std::size_t SubmitTimes = { 0 };
		std::size_t BufferSample = { 0 };
	};

	//==================================================
	//
	//	�e�탊�\�[�X�̃x�[�X�ƂȂ镔��
	//
	//==================================================
	class CLoadSoundFile
	{
	public:
		CLoadSoundFile() {}				// ������
		virtual ~CLoadSoundFile() {}	// �I��
		virtual void Update() {}

		virtual void* GetBuffer() = 0;	// ���݂̃o�b�t�@���̎擾


		virtual std::size_t GetAudioBufferSize() { return m_SoundResouce.BufferSample; }
		virtual AUDIOFORMAT* GetWaveFormat() { return &m_SoundResouce.Format; };// �T�E���h�t�@�C���̏����擾

		virtual int GetAudioChannel() { return m_SoundResouce.Format.nChannels; }
		virtual int GetAudioSpS() { return m_SoundResouce.Format.nSamplesPerSec; }

	protected:

		virtual void LoadFormat() = 0;	// �T�E���h���(�o�b�t�@��������)�擾

		// �o�b�t�@�f�[�^�ǂݍ���
		virtual std::size_t ReadDataRaw() { return 0; }

		SoundResources m_SoundResouce;	// �T�E���h���
		bool m_BufferLoadflag;			// �ǂݍ��݃t���O

		std::string FilePath;

	};
}