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
		if (Audioresourcelist.size() <= 0)
			return;

		Audioresourcelist.clear();

	}

	/// <summary>
	/// �ŏ���Preload�ݒ�̉�����ǂݍ���
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{
		// Preload�X�e�[�g�̎擾
		AudioFormatData::LoadAudioPreloadFormatData(Audioresourcelist);

		// �o�b�t�@�̊m��
		for(ResourceData itr : Audioresourcelist)
		{
			AudioDecoder::AudioBufferDecoder(&itr.preloadBuf[0], itr.data, SoundDatas[NowUsedNumb], itr.fmt, SpeakerCue.Filepath);
		}

	}

	/// <summary>
	/// �ǂݍ���buffer���擾����֐�
	/// </summary>
	/// <param name=""></param>
	void AudioReSource::GetAudioBuffer(std::string)
	{
	}
	
	/// <summary>
	/// �ǂݍ���buffer���擾����֐�
	/// </summary>
	/// <param name="Id"></param>
	void AudioReSource::GetAudioBuffer(int Id)
	{

	}

	/// <summary>
	/// ���݂̃��\�[�X��S�폜
	/// </summary>
	void AudioReSource::ReleaseResource()
	{

	}

}