#pragma once

#include<list>

#include"AudioData.h"
#include"OpenAL\AudioSpeaker\AudioSpeaker.h"

namespace htAudio
{
	/// <summary>
	/// �X�s�[�J�[�̈ꊇ�ύX�Ɏg�p����N���X
	/// </summary>
	class SpeakerManager
	{
	public:
		SpeakerManager();
		~SpeakerManager();

		void AddSpeaker(AudioSpeaker* speakerptr);		// �X�s�[�J�[�̒ǉ�
		void RemoveSpeaker(AudioSpeaker* speakerptr);	// �X�s�[�J�[�̍폜
		void AllDeleteSpeaker();						// �X�s�[�J�[�̑S�폜

		void SpeakerUpdate();							// �o�^�X�s�[�J�̍X�V

		void ControlVolume(VOLUMETYPE type,double value);	// �{�����[���̈ꊇ�ύX

	private:
		std::list<AudioSpeaker*> SpeakerList;	// AudioSpeaker���ꊇ�ύX�������肷�鎞�Ɏg�p����list
		std::array<double, VOLUMETYPE::MAX_VOLUMETYPE> VolumeArray; // �e��{�����[���̔z��

	};

}