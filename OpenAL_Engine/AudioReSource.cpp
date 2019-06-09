#include "AudioReSource.h"
#include"OpenAL/AudioFormatData/AudioFormatData.h"

namespace htAudio
{
	/// <summary>
	/// �R���X�g���N�^��Audio�o�b�t�@�̓ǂݍ���
	/// </summary>
	AudioReSource::AudioReSource()
	{
		ReadPreLoadAudio();
	}

	AudioReSource::~AudioReSource()
	{
		ReleaseResource();
	}

	/// <summary>
	/// �ŏ���Preload�ݒ�̉�����ǂݍ���
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{
		// Preload�X�e�[�g�̎擾
		AudioFormatData::LoadAudioPreloadFormatData(Audioresourcelist);

		// �ǂݍ��񂾏��̕������o�b�t�@�̊m��
		for(ResourceData itr : Audioresourcelist)
		{
			for (SoundType type : itr.soundType)
			{
				int16_t* buffer;
				AudioDecoder::AudioBufferDecoder(&buffer[0], itr.data, type, itr.fmt, itr.cueData.Filepath);
				itr.PreloadBuffer.push_back(*buffer);
			}
			
		}
	}

	/// <summary>
	/// �ǂݍ���buffer���N���[�������đ���֐�
	/// </summary>
	/// <param name=""></param>
	void AudioReSource::GetAudioBuffer(std::string cuename, AUDIOFILEFORMAT* fmt, std::list<SoundType>* type, AudioCue* cue, AudioData* data, void* buf)
	{
		for (ResourceData var : Audioresourcelist)
		{
			if (var.cueData.CueName == cuename)
			{
				fmt = &var.fmt;
				type = &var.soundType;
				cue = &var.cueData;
				data = &var.data;
				buf = &var.PreloadBuffer;
			}
		}
	}
	
	/// <summary>
	/// �ǂݍ���buffer���N���[�������đ���֐�
	/// </summary>
	/// <param name="Id"></param>
	void AudioReSource::GetAudioBuffer(int Id, AUDIOFILEFORMAT* fmt, std::list<SoundType>* type, AudioCue* cue, AudioData* data, void* buf)
	{
		for (ResourceData var : Audioresourcelist)
		{
			if (var.cueData.CueID == Id)
			{
				fmt = &var.fmt;
				type = &var.soundType;
				cue = &var.cueData;
				data = &var.data;
				buf = &var.PreloadBuffer;
			}
		}
	}

	/// <summary>
	/// ���݂̃��\�[�X��S�폜
	/// </summary>
	void AudioReSource::ReleaseResource()
	{
		if (Audioresourcelist.empty())
		{
			return;
		}
		
		for (ResourceData var : Audioresourcelist)
		{
			var.PreloadBuffer.clear();
			var.soundType.clear();
		}

		Audioresourcelist.clear();
	}

}