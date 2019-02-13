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
			return false;
		}

		vorbis_info* vi = ov_info(&Ovf,-1);

		format.Fmt.FormatType = WAVE_FORMAT_PCM;
		format.Fmt.Channels = vi->channels;
		format.Fmt.SamplesPerSec = vi->rate;
		format.Fmt.BlockSize = vi->channels * 2;
		format.Fmt.BitsPerSample = 16;
		format.Fmt.BytesPerSec = (vi->rate) * (vi->channels * 2);
		
		// ���g�p
		format.DataChunkSample = 0;

		return true;
#endif
		return false;

	}

	bool AudioDecoder::RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format)
	{
		FILE* fp;

		fopen_s(&fp, filename.c_str(), "rb");

		if (fp == NULL)
			return false;

		// RIFF�`�����N�̓ǂݍ���
		fread(format.Riff.ChunkID, 1, 4, fp);
		fread(&format.Riff.ChunkSize, 4, 1, fp);
		fread(format.Riff.FormatType, 1, 4, fp);

		// fmt�`�����N�̓ǂݍ���
		fread(format.Fmt.ChunkID, 1, 4, fp);
		fread(&format.Fmt.ChunkSize, 4, 1, fp);
		fread(&format.Fmt.FormatType, 2, 1, fp);
		fread(&format.Fmt.Channels, 2, 1, fp);
		fread(&format.Fmt.SamplesPerSec, 4, 1, fp);
		fread(&format.Fmt.BytesPerSec, 4, 1, fp);
		fread(&format.Fmt.BlockSize, 2, 1, fp);
		fread(&format.Fmt.BitsPerSample, 2, 1, fp);

		// Data�`�����N�̓ǂݍ���(������Data������)
		fread(format.Data.ChunkID, 1, 4, fp);
		fread(&format.Data.ChunkSize, 4, 1, fp);

		// ���f�[�^�܂ł̈ړ���(������͍l���Ȃ�)
		format.FirstSampleOffSet = 57;

		fclose(fp);

		format.HasGotWaveFormat = true;

		return true;

	}

	/// <summary>
	/// �I�[�f�B�I�o�b�t�@�[�ǂݍ��ݗp�̑����֐�
	/// </summary>
	bool AudioDecoder::AudioBufferDecoder(void* buf,AudioData& audiodata,SoundType type, AUDIOFILEFORMAT headerfmt, std::string filepath)
	{
		// �g���q�̔��f
		if (type.RIFFType == RIFF_WAV)
		{
			return BufferDecoderWav(headerfmt, filepath + type.AudioName + ".wav", type.Loopflag , audiodata, buf);
		}
		else if (type.RIFFType == RIFF_OGG)
		{
			return BufferDecoderOgg(audiodata, filepath + type.AudioName + ".ogg", type.Loopflag, buf);
		}

		// �����Ȃ�
		return false;
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

	/// <summary>
	/// �o�b�t�@�[�̓ǂݍ���(.wav)
	/// </summary>
	/// <param name="buf"></param>
	bool AudioDecoder::BufferDecoderWav(AUDIOFILEFORMAT& Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf)
	{
		if (Format.Fmt.Channels == 2)
		{
			unsigned long readsample = Mono16WavDecoder(Format, filename, loopflag,audiodata,buf);

			if (readsample > 0)
			{
				audiodata.NextFirstSample += readsample;
				return true;
			}
		}
		else
		{
			return false;
			// ���݂͖���
		}

		return false;
	}

	/// <summary>
	/// 16bit���m�����ō���Ă���wav�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="audiodata"></param>
	/// <param name="buf"></param>
	/// <returns></returns>
	unsigned long AudioDecoder::Mono16WavDecoder(AUDIOFILEFORMAT& Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf)
	{
		// �t�@�C���|�C���^
		FILE* fp;

		long actualSamples = 0;
		long readSample = 0;
		long ret = 0;

		long first;	// �ǂݍ��݊J�n�ʒu
		long end;	// �ǂݍ��ݏI���ʒu
		
		// �t�@�C���̃I�[�v��
		fopen_s(&fp, filename.c_str(),"rb");

		if (!buf)
			return 0;

		if (!fp)
			return 0;

		if (!Format.HasGotWaveFormat)
			return 0;

		if (first >  audiodata.DataChunkSample); 
			return 0;


		if (first + end > audiodata.DataChunkSample)
		{
			actualSamples = audiodata.DataChunkSample - first;
		}
		else
		{
			actualSamples = end;
		}
		
		while (readSample < actualSamples)
		{
			ret = fread(reinterpret_cast<uint16_t*>(buf) + readSample * Format.Fmt.BlockSize,
				Format.Fmt.BlockSize,
				actualSamples - readSample,
				fp);

			if (ret == 0)
				break;

			readSample += ret;
		}

		fclose(fp);

		audiodata.BufferSample = ret * Format.Fmt.BlockSize;

		if (readSample == 0)
		{
			if (audiodata.NextFirstSample >= audiodata.DataChunkSample && loopflag == true)
			{
				// �o�b�t�@�ǂݍ��ݏI��
				// ���[�v�p�ɓǂݍ��݈ʒu��������
				audiodata.NextFirstSample = 0;
			}
		}

		return readSample;
	}

	//====================================
	//	Data�����̎擾
	//	�X�e���I�ǂݍ��݂����ǎg���\�肪�Ȃ��̂ł����
	//	�ȑO�̏�Ԃ�ύX�����Ȃ��ŃR�s�[���Ă���
	//====================================
	/*std::size_t Streo16WavDecoder(long first, long end, float* left, float* right)
	{
		FILE* fp;

		fopen_s(&fp, m_SoundResouce.PresetSoundName.c_str(), "rb");

		if (!fp)
			return 0;

		if (!m_SoundResouce.HasGotWaveFormat)
			return 0;

		if (first >= m_SoundResouce.DataChunkSample)
			return 0;

		std::size_t actualSamples = first + end > m_SoundResouce.DataChunkSample ? m_SoundResouce.DataChunkSample - first : end;

		if (fseek(fp, m_SoundResouce.firstSampleOffSet + first * m_SoundResouce.Format.nBlockAlign, SEEK_SET) != 0)
			return 0;

		std::size_t readSamples = 0;

		for (; readSamples < actualSamples; ++readSamples)
		{
			// 1 �T���v���ǂݍ���
			uint32_t data[2];
			std::size_t ret = fread(data, m_SoundResouce.Format.nBlockAlign, 1, fp);	// Warning: 3 �`�����l���ȏオ����ƃo�b�t�@�I�[�o�[����
			if (ret == 0) break;

			
			// 16bit signed: -32768...0...32767
			
			int16_t * data_s16 = reinterpret_cast<int16_t *>(data);
			if (m_SoundResouce.Format.nChannels == 1)
			{
				float l = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f :
					static_cast<float>(data_s16[0]) / 32767.0f;
				left[readSamples] = l;
				if (right) right[readSamples] = l;
			}
			else
			{
				float l = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f :
					static_cast<float>(data_s16[0]) / 32767.0f;
				float r = (data_s16[1] < 0) ? static_cast<float>(data_s16[1]) / 32768.0f :
					static_cast<float>(data_s16[1]) / 32767.0f;
				if (right)
				{
					left[readSamples] = l;
					right[readSamples] = r;
				}
				else
				{
					left[readSamples] = (l + r) * 0.5f;
				}
			}
			
			break;
			
		}
		return readSamples;
	}*/

	//std::size_t CLoadWave::PreloadBuffer()
	//{
	//	size_t first = 0;
	//	size_t last = m_SoundResouce.DataChunkSize;
	//	PrimaryMixed = std::vector<std::size_t>(last);
	//	//PrimaryMixed = new std::size_t[last];
	//	std::size_t readSample = ReadDataRaw((long)first, (long)last, &(PrimaryMixed[0]));
	//	m_SoundResouce.BufferSample = m_SoundResouce.DataChunkSize;
	//	return readSample;
	//}
}