#pragma once
#include"AudioCommand.h"
#include"AudioManager.h"

namespace htAudio {

	class PlayCommand : public AudioCommand
	{
	public:
		PlayCommand(OrderFormat fmt);
		~PlayCommand();

		// DLL“àˆ——p
		virtual bool Execute();
		
	private:
		// DLL“àˆ——p
		bool Play(int source);
	};

}