#include "AudioReSource.h"
#include"OpenAL/AudioFormatData/AudioFormatData.h"
#include <algorithm>

namespace htAudio
{
	/// <summary>
	/// �R���X�g���N�^��Audio�o�b�t�@�̓ǂݍ���
	/// </summary>
	AudioReSource::AudioReSource()
	{
		ReadCueFormatData();
		ReadPreLoadAudio();
	}

	AudioReSource::~AudioReSource()
	{
		ReleaseResource();
		ReleaseFormatData();
	}

	/// <summary>
	/// �ŏ���Preload�ݒ�̉�����ǂݍ���
	/// </summary>
	void AudioReSource::ReadPreLoadAudio()
	{
		// Preload�X�e�[�g�̎擾
		if (Audioresourcelist.empty())
			return;

		// �ǂݍ��񂾏��̕������o�b�t�@�̊m��
		for(AudioCue itr : Audioresourcelist)
		{
			for (SoundType type : itr.AudioInfo)
			{
				int16_t* buffer = new int16_t();
				
				// TODO: �o�b�t�@�̓ǂݍ��݂ƃt�H�[�}�b�g�̏�����
				AudioDecoder::LoadRIFFFormat(type.AudioFormat,type, itr.Filepath);
				AudioDecoder::AudioPreloadBufferDecoder(&buffer[0], type, type.AudioFormat, itr.Filepath);
				
				BufferMap.insert(std::make_pair(type.AudioID, buffer));
			}
		}
	}

	/// <summary>
	/// �ǂݍ���buffer���N���[�������đ���֐�
	/// </summary>
	/// <param name=""></param>
	void AudioReSource::GetAudioBuffer(SoundType Target, void* buf)
	{
		if (BufferMap.empty())
			return;

		for (auto var : BufferMap)
		{
			if (var.first == Target.AudioID)
			{
				// TODO: Buffer�R�s�[
				buf = &var.second;
				break;
			}
		}
	}
	
	/// <summary>
	/// ���݂̃��\�[�X��S�폜
	/// </summary>
	void AudioReSource::ReleaseResource()
	{
		if (BufferMap.empty())
			return;
		
		for (auto bufmap : BufferMap)
		{
			delete bufmap.second;
		}

		BufferMap.clear();
	}

	/// <summary>
	/// Cue�̃t�H�[�}�b�g�f�[�^���ꊇ�œǂݍ���
	/// </summary>
	void AudioReSource::ReadCueFormatData()
	{
		AudioFormatData::LoadAudioPreloadFormatData(Audioresourcelist);
	}

	/// <summary>
	/// �w���Cue�f�[�^�����������Ă���
	/// </summary>
	/// <param name="CueId"></param>
	AudioCue AudioReSource::GetFormatData(int CueId)
	{
		AudioCue selectCue;

		if (Audioresourcelist.empty())
			return selectCue;

		for (auto cue : Audioresourcelist)
		{
			if (cue.CueID != CueId)
				continue;

			selectCue = cue;
		}

		return selectCue;

	}

	/// <summary>
	/// �w���Cue�f�[�^�����������Ă���
	/// </summary>
	/// <param name="CueName"></param>
	AudioCue AudioReSource::GetFormatData(std::string CueName)
	{
		AudioCue selectCue;

		if (Audioresourcelist.empty())
			return selectCue;

		for (auto cue : Audioresourcelist)
		{
			if (cue.CueName != CueName)
				continue;

			selectCue = cue;
		}

		return selectCue;
	}

	/// <summary>
	/// �擾�����t�H�[�}�b�g�̔j��
	/// </summary>
	void AudioReSource::ReleaseFormatData()
	{
		if (Audioresourcelist.empty())
			return;

		for (auto cue : Audioresourcelist)
		{
			cue.CueEffect.clear();
			cue.AudioInfo.clear();
		}
		Audioresourcelist.clear();
	}


}