#include "PlayCommand.h"

#include<AL/efx.h>

namespace htAudio {


	PlayCommand::PlayCommand(OrderFormat fmt)
	{
		OrderFmt = fmt;
	}

	PlayCommand::~PlayCommand()
	{

	}

	/// <summary>
	/// �Đ��I�[�f�B�I�̍Đ�
	/// </summary>
	/// <param name="source"></param>
	/// <returns></returns>
	bool PlayCommand::Play(int source)
	{
		ALuint _source = (ALuint)source;
		alSourcePlay(_source);
		return true;
	}

}