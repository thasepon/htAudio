#include "SetBufCommand.h"
#include<AL/efx.h>
#include<AL/efx-creative.h>

namespace htAudio
{
	SetBufCommand::~SetBufCommand()
	{
	}

	bool SetBufCommand::SetDataBuffer(int bufNumb, int channel, void* bufdata, int fq, int bufsize) 
	{
		// �o�b�t�@�ԍ��̐ݒ�
		ALuint _buffer = (ALuint)bufNumb;

		// �I���o�b�t�@���Ȃ��ꍇ�̏���
		if (!bufNumb)
		{
			alGenBuffers(1, &_buffer);
			return false;
		}

		// ���m�X�e�̔��f
		ALenum format;
		if (channel == 1)
		{
			format == AL_FORMAT_MONO16;
		}
		else
		{
			format == AL_FORMAT_STEREO16;
		}

		// �o�b�t�@�̐ݒ�
		alBufferData(bufNumb, format, bufdata, bufsize, fq);

		return true;

	}
}