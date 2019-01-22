#pragma once

#include<Windows.h>
#include<string>
#include<vector>
#include<list>

namespace htAudio
{
	// ================= ���萔�^ =================== //
	#define USE_OGG_LIB

	// ================= ���񋓌^ =================== //
	
	// �t�@�C���g���q
	enum RIFFType
	{
		RIFF_WAV,
		RIFF_OGG,
		RIFF_MAX
	};

	// �o�b�t�@�̃��[�h�^�C�v
	enum AudioLoadType
	{
		STREAM_LOAD,
		PRE_LOAD,
		MAX_LOAD
	};

	// �G�t�F�N�g�̎��
	enum EFFECTSNUM
	{
		REVERB = 0,
		CHORUS,
		DISTORTION,
		ECHO,
		FLANGER,
		FQ,
		PITCH,
		WAH,
		EQ,
		I3DAUDIO,
		MAX_EFFECTS,
	};

	enum ORDERTYPE 
	{
		PLAY,
		STOP,
		PAUSE,
		MAX_ORDER
	};

	// ================= ���\���� =================== //

	struct OrderFormat
	{
		UINT16 SourceID;
		UINT16 Latency;
	};

	struct RIFFChunk
	{
		UCHAR RIFFID[4];
		WORD FileSize;
		UCHAR WaveFormatType[4];
	};

	struct FormatChunk
	{
		UCHAR FmtID[4];		// fmt�`�����N
		unsigned long ChunkSize;// fmt�`�����N�̃o�C�g��
		WORD FormatType;		// PCM�̎��
		WORD Channels;			// �`�����l����
		DWORD SamplesPerSec;	// �T���v�����O���[�g
		DWORD BytesPerSec;	// �f�[�^�]�����x
		WORD  BlockSize;		// �u���b�N�T�C�Y
		WORD  BitsPerSample;	// �T���v��������̃r�b�g��
	};

	struct DataChunk
	{
		UCHAR DataID[4];			// fmt�`�����N
		std::size_t DataChunkSize;	// �f�[�^�o�b�t�@�T�C�Y
		std::size_t BufData;
	};

	// �w�b�_�[���
	struct AUDIOFILEFORMAT{
		RIFFChunk Riff;
		FormatChunk Fmt;
		DataChunk Data;
		long FirstSampleOffSet; // Buffer�̊J�n�ʒu
		std::size_t DataChunkSample; // �T���v�����O���
	};

	// �T�E���h���̂��̂̏��
	struct SoundType {
		int AudioID;				// Audio�̏��
		std::string AudioName;		// �I�[�f�B�I�t�@�C���̖��O
		double b3DAudio;			// 3DAudio���g�p���邩�ǂ���
		std::string Cue;			// Cue�̖��O
		std::string SubGroup;		// �����Ă���O���[�v
		std::string MaterialObj;	// �����Ă���}�e���A��
		bool Loopflag;				// ���[�v�t���O
		AudioLoadType StreamType;	// �X�g���[�~���O�^�C�v
		RIFFType RIFFType;			// �t�@�C���g���q�̎��
		double LowVolume;			// �Œቹ��
		double DefaultVolume;		// �f�t�H���g����
		double MaxVolume;			// �ő剹��
		bool CreateFlag;			// �쐬�t���O
	};

	// Audio���ێ����Ă�����
	struct AudioData {
		std::string Filepath;				// �t�@�C���p�X
		std::string	PresetSoundName;		// �I�[�f�B�I�t�@�C����
		int PlayTime;						// �Đ�����
		bool LoopSound;						// ���[�v���
		long TotalreadBufSize;				// �ǂ݂��񂾃o�b�t�@��
		long ReadBufSize;					// ��x�ɓǂݍ��ރo�b�t�@��
		std::size_t NextFirstSample = { 0 };
		std::size_t SubmitTimes = { 0 };	// �ǂ̃o�b�t�@���g�p���邩�̔���
		std::size_t BufferSample = { 0 };
	};

	// AudioInfo
	struct AudioResources
	{
		bool HasGotWaveFormat;		// �I�[�f�B�I�t�@�C���̏����擾�o���Ă��邩�ǂ���
		AudioData Data;				// Audio�̃f�[�^(�g���܂킵����\��)
		AUDIOFILEFORMAT Format;		// �w�b�_�[���
		std::vector<SoundType> Soundtypes;		// XML���瓾�����(�����̃f�[�^������܂�)
		std::vector<char> PrimaryMixed;	// �o�b�t�@�ۑ�[1]
		std::vector<char> SecondMixed;	// �o�b�t�@�ۑ�[2]
	};

}