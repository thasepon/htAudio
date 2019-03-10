#include "PlayCommand.h"

#include<AL/efx.h>

namespace htAudio {


	PlayCommand::PlayCommand(OrderFormat fmt) : AudioCommand()
	{
		OrderFmt = fmt;
	}

	PlayCommand::~PlayCommand()
	{

	}

	bool PlayCommand::Execute() 
	{ 
		if (TimeCtrlCmd() == false)
			return false;

		Play(OrderFmt.SourceID);

		return true;
	}

	/// <summary>
	/// �Đ��I�[�f�B�I�̍Đ�
	/// </summary>
	/// <param name="source"></param>
	/// <returns></returns>
	bool PlayCommand::Play(int source)
	{
		if (alIsSource(source) == false)
		{
			printf("%d �\�[�X���L���ł͂���܂���B\n", source);
			return false;
		}

		ALuint _source = (ALuint)source;
		alSourcePlay(_source);

		printf("%d ���Đ����܂��B\n", source);

		return true;
	}

}