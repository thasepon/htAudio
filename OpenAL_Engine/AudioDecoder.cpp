#include "AudioDecoder.h"

namespace htAudio
{

	AudioDecoder::AudioDecoder()
	{
	}


	AudioDecoder::~AudioDecoder()
	{
	}

#pragma region Header�ǂݎ��

	/// <summary>
	/// Ogg,wav�t�@�C���̃w�b�_�[�����̓ǂݍ���
	/// </summary>
	bool AudioDecoder::LoadRIFFFormat(AUDIOFILEFORMAT& headerfmt, SoundType audiodata, std::string filepath)
	{

		if (audiodata.RIFFType == RIFF_WAV)
		{
			return RIFFDecoderWave(filepath + audiodata.AudioName+".wav", headerfmt);
		}
		else if (audiodata.RIFFType == RIFF_OGG)
		{
			return RIFFDecoderOgg(filepath + audiodata.AudioName+".ogg", headerfmt);
		}

		// �����Ȃ�
		return false;

	}

	bool AudioDecoder::RIFFDecoderOgg(std::string filename, AUDIOFILEFORMAT& format)
	{

#ifdef USE_OGG_LIB
		OggVorbis_File Ovf;

		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Ogg�t�@�C���I�[�v���̎��s
			printf("�w�b�_�[���̓ǂݎ��Ɏ��s���܂���");
			return false;
		}

		vorbis_info* vi = ov_info(&Ovf,-1);

		format.Fmt.FormatType = WAVE_FORMAT_PCM;
		format.Fmt.Channels = vi->channels;
		format.Fmt.SamplesPerSec = vi->rate;
		format.Fmt.BlockSize = vi->channels * 2;
		format.Fmt.BitsPerSample = 16;
		format.Fmt.BytesPerSec = (vi->rate) * (vi->channels * 2);

		return true;
#endif
		return false;

	}

	bool AudioDecoder::RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format)
	{
		FILE* fp;

		fopen_s(&fp, filename.c_str(), "rb");

		// �I�[�v�����s
		if (!fp)
		{
			printf("�w�b�_�[���̓ǂݎ��Ɏ��s���܂���");
			return false;
		}

		long offset = 0;

		printf("%s���J���܂�\n", filename.c_str());

		while (true)
		{
			char chunksignature[4] = { 0 };

			if (fread(chunksignature, 4, 1, fp) == 0)
			{
				break;
			}

			offset += 4;

			if (strncmp(chunksignature, "RIFF ", 4) == 0)
			{
				// RIFF�`�����N�̓ǂݍ���
				strcpy(format.Riff.ChunkID, chunksignature);
				offset += fread(&format.Riff.ChunkSize, 4, 1, fp);
				offset += fread(format.Riff.FormatType, 4, 1, fp);

				printf("RIFF :: %s - %d - %s \n", 
					format.Riff.ChunkID, 
					format.Riff.ChunkSize, 
					format.Riff.FormatType);

			}

			if (strncmp(chunksignature, "fmt ", 4) == 0)
			{
				// fmt�`�����N�̓ǂݍ���
				strcpy(format.Fmt.ChunkID, chunksignature);
				offset += fread(&format.Fmt.ChunkSize, 4, 1, fp);
				offset += fread(&format.Fmt.FormatType, 2, 1, fp);
				offset += fread(&format.Fmt.Channels, 2, 1, fp);
				offset += fread(&format.Fmt.SamplesPerSec, 4, 1, fp);
				offset += fread(&format.Fmt.BytesPerSec, 4, 1, fp);
				offset += fread(&format.Fmt.BlockSize, 2, 1, fp);
				offset += fread(&format.Fmt.BitsPerSample, 2, 1, fp);

				printf("FMT :: %s - %d - %d - %d - %d - %d - %d - %d \n", 
					format.Fmt.ChunkID, 
					format.Fmt.ChunkSize, 
					format.Fmt.FormatType,
					format.Fmt.Channels,
					format.Fmt.SamplesPerSec,
					format.Fmt.BytesPerSec,
					format.Fmt.BlockSize,
					format.Fmt.BitsPerSample);

			}

			if (strncmp(chunksignature, "data", 4) == 0)
			{
				// Data�`�����N�̓ǂݍ���(������Data������)
				strcpy(format.Data.ChunkID, chunksignature);
				offset += fread(&format.Data.ChunkSize, 4, 1, fp);

				printf("Data :: %s - %d \n",
					format.Data.ChunkID,
					format.Data.ChunkSize);
			}
		}

		if (format.Data.ChunkSize == 0)
		{
			memcpy(format.Data.ChunkID, "data", 4);
			format.Data.ChunkSize = offset;
		}

		// ���f�[�^�܂ł̈ړ���(������͍l���Ȃ�)
		format.FirstSampleOffSet = 48;

		fclose(fp);
		
		return true;

	}

#pragma endregion

	/// <summary>
	/// �I�[�f�B�I�o�b�t�@�[�ǂݍ��ݗp�̑����֐�
	/// </summary>
	/// <param name="buf">�o�b�t�@�̕ۑ��|�C���^</param>
	/// <param name="audiodata">�X�g���[���f�[�^(nullptr��Preload)</param>
	/// <param name="type">�Ώۂ̃T�E���h���</param>
	/// <param name="headerfmt">�w�b�_�[���</param>
	/// <param name="filepath">�t�@�C���̂���t�H���_�[</param>
	/// <returns></returns>
	bool AudioDecoder::AudioBufferDecoder(void* buf,AudioData* audiodata,SoundType type, AUDIOFILEFORMAT headerfmt, std::string filepath)
	{
		bool loadflag = false;

		// �g���q�̔��f
		if (type.RIFFType == RIFF_WAV)
		{
			loadflag = BufferDecoderWav(headerfmt, filepath + type.AudioName + ".wav", type.Loopflag , audiodata, buf);
		}
		else if (type.RIFFType == RIFF_OGG)
		{
			loadflag = BufferDecoderOgg(headerfmt, filepath + type.AudioName + ".ogg", type.Loopflag, audiodata, buf);
		}

		// �����Ȃ�
		return loadflag;
	}

	/// <summary>
	/// �o�b�t�@�[�̓ǂݍ���(.ogg)
	/// </summary>
	/// <param name="Format">Header���</param>
	/// <param name="filename">�Ώۂ̃t�@�C���p�X</param>
	/// <param name="loopflag">���[�v�t���O</param>
	/// <param name="audiodata">�X�g���[���f�[�^(nullptr��Preload)</param>
	/// <param name="buf">�o�b�t�@�{��</param>
	/// <returns>�����t���O</returns>
	bool AudioDecoder::BufferDecoderOgg(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData* audiodata,void* buf)
	{
		unsigned long requestsize = 0;
		int bitstream = 0;
		ULONG readsize = 0;
		ULONG comsize = 0;
		OggVorbis_File Ovf;
		
		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Ogg�t�@�C���I�[�v���̎��s
			printf("�T�E���h�t�@�C���̓ǂݎ��Ɏ��s���܂���");
			return false;
		}

		if (audiodata == nullptr)
		{
			requestsize = Format.Data.ChunkSize;
		}
		else 
		{
			requestsize = audiodata->ReadBufSize;
			ov_pcm_seek(&Ovf, audiodata->NextFirstSample);
		}


		// �ǂ݂��ݕ���
		while (1)
		{
			readsize = ov_read(&Ovf, (char*)((char*)buf + comsize), requestsize, 0, 2, 1, &bitstream);
			
			// ���[�܂œǂݍ��ݏI��
			if (readsize == 0)
			{
				// ���[�v����������ꍇ�͓ǂݍ��݈ʒu��擪�ɖ߂��B
				if (loopflag == true)
				{
					ov_time_seek(&Ovf,0.0);
				}
				else 
				{
					// ���얳��
					break;
				}
			}
			// ����ǂ݂��񂾗ʂ�ۑ�
			comsize += readsize;
			
			// �w��ʂ̃o�b�t�@���擾�o������I��
			if (comsize >= requestsize)
			{
				break;
			}

			// ���ɒB���Ă��Ȃ��ꍇ�͎c��̕���Request����
			if ((requestsize - comsize) > 0)
			{
				requestsize -= comsize;
			}

		}

		if (audiodata != nullptr)
		{
			audiodata->NextFirstSample = comsize;
		}

		return true;
	}

	/// <summary>
	/// �o�b�t�@�[�̓ǂݍ���(.wav)
	/// </summary>
	/// <param name="Format">Header���</param>
	/// <param name="filename">�Ώۂ̃t�@�C���p�X</param>
	/// <param name="loopflag">���[�v�t���O</param>
	/// <param name="audiodata">�X�g���[���f�[�^(nullptr��Preload)</param>
	/// <param name="buf">�o�b�t�@�{��</param>
	/// <returns>�����t���O</returns>
	bool AudioDecoder::BufferDecoderWav(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData* audiodata, void* buf)
	{
		FILE* fp = nullptr;			// �t�@�C���|�C���^

		ULONG samplesize = 0;
		ULONG freadsize = 0;
		
		ULONG _nextFirstSample = 0;
		ULONG _readBufSize = 0;

		// �t�@�C���̃I�[�v��
		fopen_s(&fp, filename.c_str(), "rb");
		if (!fp)
		{
			printf("�T�E���h�t�@�C���̓ǂݎ��Ɏ��s���܂���");
			return false;
		}

		// AudioData�����݂��Ȃ��ꍇ�̏���
		if (audiodata == nullptr)
		{
			_nextFirstSample = Format.FirstSampleOffSet;
			_readBufSize = Format.Data.ChunkSize;

		}
		else 
		{
			_nextFirstSample = audiodata->NextFirstSample;
			_readBufSize = audiodata->ReadBufSize;

		}

		// �o�b�t�@�ǂݍ��ݗ�
		fseek(fp, _nextFirstSample, SEEK_CUR);

		while (samplesize < _readBufSize)
		{
			freadsize = fread(
				buf,
				_readBufSize,
				1,
				fp);

			// �ǂݍ��݂���������
			if (freadsize == 0)
			{
				break;
			}

			samplesize += freadsize;
			freadsize = 0;

		}

		// �I������
		fclose(fp);

		// ���[�v����
		if (samplesize == 0 && audiodata != nullptr)
		{
			if (loopflag >= 0 && loopflag)
			{
				audiodata->NextFirstSample = Format.FirstSampleOffSet;
			}
		}
		
		return true;

	}

}