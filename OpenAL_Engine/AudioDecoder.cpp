#include "AudioDecoder.h"

namespace htAudio
{

	AudioDecoder::AudioDecoder()
	{
	}


	AudioDecoder::~AudioDecoder()
	{
	}

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

	/// <summary>
	/// �I�[�f�B�I�o�b�t�@�[�ǂݍ��ݗp�̑����֐�
	/// </summary>
	bool AudioDecoder::AudioBufferDecoder(void* buf
		,AudioData& audiodata
		,SoundType type
		, AUDIOFILEFORMAT headerfmt
		, std::string filepath)
	{
		bool loadflag = false;

		// �g���q�̔��f
		if (type.RIFFType == RIFF_WAV)
		{
			loadflag = BufferDecoderWav(headerfmt, filepath + type.AudioName + ".wav", type.Loopflag , audiodata, buf);
		}
		else if (type.RIFFType == RIFF_OGG)
		{
			loadflag = BufferDecoderOgg(audiodata, filepath + type.AudioName + ".ogg", type.Loopflag, buf);
		}

		// �����Ȃ�
		return loadflag;
	}

	/// <summary>
	/// Preload�̃o�b�t�@�ǂݍ���
	/// (�ꕔ�K�v�̂Ȃ��������������̂ō쐬)
	/// </summary>
	/// <param name="buf"></param>
	/// <returns></returns>
	bool AudioDecoder::AudioPreloadBufferDecoder(void* buf
		, SoundType type
		, AUDIOFILEFORMAT headerfmt
		, std::string filepath)
	{
		bool loadflag = false;

		// �g���q�̔��f
		if (type.RIFFType == RIFF_WAV)
		{
			PreloadWavDecoder(headerfmt, filepath + type.AudioName + ".wav", type.Loopflag, buf);
		}
		else if (type.RIFFType == RIFF_OGG)
		{
			loadflag = PreloadOggDecoder( filepath + type.AudioName + ".wav", type.Loopflag, buf);
		}
	}


	/// <summary>
	/// �o�b�t�@�[�̓ǂݍ���(.wav)
	/// </summary>
	/// <param name="buf"></param>
	bool AudioDecoder::BufferDecoderOgg(AudioData& audiodata, std::string filename, bool loopflag, void* buf)
	{
		unsigned long requestsize = audiodata.ReadBufSize;
		int bitstream = 0;
		int readsize = 0;
		UINT comsize = 0;
		OggVorbis_File Ovf;
		
		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Ogg�t�@�C���I�[�v���̎��s
			printf("�T�E���h�t�@�C���̓ǂݎ��Ɏ��s���܂���");
			return false;
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
					audiodata.TotalreadBufSize = 0;
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
		// ���݂̓ǂݍ��ݗʂ����Z
		audiodata.TotalreadBufSize += comsize;
		
		return true;
	}

	unsigned long AudioDecoder::StreamOggDecoder(AudioData& audiodata, std::string filename, bool loopflag, void* buf)
	{
		unsigned long requestsize = audiodata.ReadBufSize;
		int bitstream = 0;
		int readsize = 0;
		UINT comsize = 0;
		OggVorbis_File Ovf;

		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Ogg�t�@�C���I�[�v���̎��s
			printf("�T�E���h�t�@�C���̓ǂݎ��Ɏ��s���܂���");
			return false;
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
					ov_time_seek(&Ovf, 0.0);
					audiodata.TotalreadBufSize = 0;
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
		// ���݂̓ǂݍ��ݗʂ����Z
		audiodata.TotalreadBufSize += comsize;
	}

	unsigned long AudioDecoder::PreloadOggDecoder(AudioData& audiodata, std::string filename, bool loopflag, void* buf)
	{
		unsigned long requestsize = audiodata.ReadBufSize;
		int bitstream = 0;
		int readsize = 0;
		UINT comsize = 0;
		OggVorbis_File Ovf;

		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Ogg�t�@�C���I�[�v���̎��s
			printf("�T�E���h�t�@�C���̓ǂݎ��Ɏ��s���܂���");
			return false;
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
					ov_time_seek(&Ovf, 0.0);
					audiodata.TotalreadBufSize = 0;
				}
				else
				{
					// ���얳��
					break;
				}
			}
			// ����ǂ݂��񂾗ʂ�ۑ�
			comsize += readsize;

		}
		// ���݂̓ǂݍ��ݗʂ����Z
		audiodata.TotalreadBufSize += comsize;
	}

	/// <summary>
	/// �o�b�t�@�[�̓ǂݍ���(.wav)
	/// </summary>
	/// <param name="buf"></param>
	bool AudioDecoder::BufferDecoderWav(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf)
	{
		// 8bit�͍l���܂���
		if (!buf)
		{
			printf("�o�b�t�@�̃T�C�Y�̊m�ەs��");
			return false;
		}

		// Stereo16bit
		unsigned long readsample = 0;

		readsample = StreamWavDecoder(Format, filename, loopflag, audiodata, buf);

		if (readsample > 0)
		{
			audiodata.NextFirstSample += readsample;
			return true;
		}
		
		printf("�T���v���̓ǂݍ��݂Ɏ��s���܂���\n");
		return false;
	}

	/// <summary>
	/// wav�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="audiodata"></param>
	/// <param name="buf"></param>
	/// <returns></returns>
	unsigned long AudioDecoder::StreamWavDecoder(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf)
	{

		FILE* fp = nullptr;			// �t�@�C���|�C���^
		int readsize = 0;
		// �t�@�C���̃I�[�v��
		fopen_s(&fp, filename.c_str(), "rb");
		
		if (!fp)
		{
			printf("�T�E���h�t�@�C���̓ǂݎ��Ɏ��s���܂���");
			return 0;
		}

		long samplesize = 0;
		long freadsize = 0;
		int cnt = 0;

		// �o�b�t�@�ǂݍ��ݗ�
		fseek(fp, audiodata.NextFirstSample, SEEK_CUR);

		while (samplesize < audiodata.ReadBufSize)
		{
			freadsize = fread(
				reinterpret_cast<int16_t*>(buf) + cnt,
				Format.Fmt.BlockSize / Format.Fmt.Channels,
				1,
				fp);

			// �ǂݍ��߂Ȃ������ꍇ�̏���
			if (freadsize == 0)
			{
				readsize = samplesize;
				break;
			}

			samplesize += freadsize;
			freadsize = 0;
			cnt++;

		}
		readsize = samplesize;
		

		// �I������
		fclose(fp);

		// ���[�v����
		if (readsize == 0)
		{
			if (loopflag >= 0)
			{
				// �o�b�t�@�ǂݍ��ݏI��
				// ���[�v�p�ɓǂݍ��݈ʒu��������
				audiodata.NextFirstSample = Format.FirstSampleOffSet;
			}
		}

		return readsize;
	}

	unsigned long AudioDecoder::PreloadWavDecoder(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, void* buf)
	{
		FILE* fp = nullptr;			// �t�@�C���|�C���^
		int readsize = 0;
		// �t�@�C���̃I�[�v��
		fopen_s(&fp, filename.c_str(), "rb");

		if (!fp)
		{
			printf("�T�E���h�t�@�C���̓ǂݎ��Ɏ��s���܂���");
			return 0;
		}

		long samplesize = 0;
		long freadsize = 0;
		int cnt = 0;

		// �o�b�t�@�ǂݍ��ݗ�
		fseek(fp, audiodata.NextFirstSample, SEEK_CUR);

		// �ǂݍ��ݏI���܂œǂݍ���
		while (1)
		{
			freadsize = fread(
				reinterpret_cast<int16_t*>(buf) + cnt,
				Format.Fmt.BlockSize / Format.Fmt.Channels,
				1,
				fp);

			// �ǂݍ��߂Ȃ������ꍇ�̏���
			if (freadsize <= 0)
			{
				readsize = samplesize;
				break;
			}

			samplesize += freadsize;
			freadsize = 0;
			cnt++;

		}
		readsize = samplesize;

		// �I������
		fclose(fp);

		// ���[�v����
		if (readsize == 0)
		{
			if (loopflag >= 0)
			{
				// �o�b�t�@�ǂݍ��ݏI��
				// ���[�v�p�ɓǂݍ��݈ʒu��������
				audiodata.NextFirstSample = Format.FirstSampleOffSet;
			}
		}

		return readsize;
	}


}