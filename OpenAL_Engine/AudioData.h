#pragma once

#include<Windows.h>
#include<string>
#include<vector>
#include<list>

namespace htAudio
{
	// ================= ���O���[�o�� =================== //

	// ================= ���萔�^ =================== //
	#define USE_OGG_LIB
	
	// ================= ���񋓌^ =================== //
	
	// �t�@�C���g���q
	enum RIFFType
	{
		RIFF_WAV = 0,
		RIFF_OGG,
		RIFF_MAX
	};

	// �o�b�t�@�̃��[�h�^�C�v
	enum AudioLoadType
	{
		STREAM_LOAD = 0,
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
		CONE,
		MAX_EFFECTS,
	};

	enum ORDERTYPE 
	{
		PLAY,
		STOP,
		PAUSE,
		MAX_ORDER
	};

	enum VOLUMETYPE
	{
		ALL,
		BGM,
		SE,
		VOICE,
		MAX_VOLUMETYPE
	};

	// ================= ���\���� =================== //

	struct OrderFormat
	{
		uint16_t SourceID;
		double Latency;
	};

	struct DataChunk
	{
		char ChunkID[4];	// fmt�`�����N
		unsigned long ChunkSize;	// �f�[�^�o�b�t�@�T�C�Y
	};

	struct RIFFChunk
	{
		char ChunkID[4];
		unsigned short ChunkSize;
		unsigned char FormatType[4];
	};

	struct FormatChunk
	{
		char ChunkID[4];			// fmt�`�����N
		unsigned long ChunkSize;		// fmt�`�����N�̃o�C�g��
		unsigned short FormatType;		// PCM�̎��
		unsigned short Channels;		// �`�����l����
		unsigned long SamplesPerSec;	// �T���v�����O���[�g
		unsigned long BytesPerSec;		// �f�[�^�]�����x
		unsigned short BlockSize;		// �u���b�N�T�C�Y
		unsigned short BitsPerSample;	// �T���v��������̃r�b�g��
	};

	// �t�@�C���̏��
	struct AUDIOFILEFORMAT {
		RIFFChunk Riff;
		FormatChunk Fmt;
		DataChunk Data;
		long FirstSampleOffSet; // Buffer�̊J�n�ʒu
		bool HasGotWaveFormat;		// �I�[�f�B�I�t�@�C���̏����擾�o���Ă��邩�ǂ���
	};

	// ���X�i�[�R�[���̃X�e�[�^�X�p
	struct ConeState
	{
		double ConeOuterGain;	// �R�[���̊O���Q�C�����l
		double InnerAngle;		// �����̊p�x
		double OuterAngle;		// �O���̊p�x
	};

	struct EffectState
	{
		EFFECTSNUM UseEffect;
		std::string UseElement;
	};


	// �T�E���h�̏����l�A�ݒ���
	struct SoundType {
		int AudioID;				// Audio�̏��
		std::string AudioName;		// �I�[�f�B�I�t�@�C���̖��O
		std::string Cue;			// Cue�̖��O
		std::string MaterialObj;	// �����Ă���}�e���A��
		AudioLoadType StreamType;	// �X�g���[�~���O�^�C�v
		RIFFType RIFFType;			// �t�@�C���g���q�̎��
		double DefaultVolume;		// �f�t�H���g����
		double MaxVolume;			// �ő剹��
		bool CreateFlag;			// �쐬�t���O
		bool Loopflag;				// ���[�v�t���O
	};

	// Cue(Soundtype�̑�܂Ƃ�)�̍\����
	struct AudioCue
	{
		int CueID;							// Audio�̏��
		std::string Filepath;				// �t�@�C���p�X
		std::string	CueName;				// Cue�t�@�C����
		double Volume;						// �{�����[��
		VOLUMETYPE VolType;					// �{�����[���̃^�C�v
		bool Loopflag;						// ���[�v�t���O
		std::vector<EffectState> CueEffect;	// Cue�ɓK��������G�t�F�N�g�̈ꗗ
	};

	// Speaker���̏��
	struct AudioData {
		int PlayTime;						// �Đ�����
		long TotalreadBufSize;				// �ǂ݂��񂾃o�b�t�@��
		long ReadBufSize;					// ��x�ɓǂݍ��ރo�b�t�@��
		unsigned long NextFirstSample = { 0 };
		unsigned long SubmitTimes = { 0 };	// �ǂ̃o�b�t�@���g�p���邩�̔���
		unsigned long BufferSample = { 0 };
		long DataChunkSample; // �T���v�����O���
	};

	

}