#include "AudioReSource.h"

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
		if (AudioresourceMap.size() <= 0)
			return;

		for (auto buf : AudioresourceMap)
		{
			delete buf.DataBuffer;
		}
		AudioresourceMap.clear();

	}

	/// <summary>
	/// �ŏ���Preload�ݒ�̉�����ǂݍ���
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{

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
	/// ���ݎg�p���Ă���
	/// </summary>
	void AudioReSource::ReleaseResource()
	{
	}

}