#include "SetBufCommand.h"
#include<AL/efx.h>
#include<AL/efx-creative.h>

namespace htAudio
{
	SetBufCommand::~SetBufCommand()
	{
	}
	
	bool SetBufCommand::Execute(int bufNumb, int channel, void* bufdata, int fq, int bufsize)
	{ 
		bool flag = false;

		flag = SetDataBuffer(bufNumb, channel, bufdata, fq, bufsize);

		return  flag;
	}
	
	bool SetBufCommand::SetDataBuffer(int bufNumb, int channel, void* bufdata, int fq, int bufsize) 
	{
		// バッファ番号の設定
		ALuint _buffer = (ALuint)bufNumb;

		// 選択バッファがない場合の処理
		if (!bufNumb)
		{
			alGenBuffers(1, &_buffer);
			return false;
		}

		// モノステの判断
		ALenum format = AL_FORMAT_MONO16;

		if (channel == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else if (channel == 2)
		{
			format = AL_FORMAT_STEREO16;
		}

		// バッファの設定
		alBufferData(bufNumb, format, bufdata, bufsize, fq);

		return true;

	}
}