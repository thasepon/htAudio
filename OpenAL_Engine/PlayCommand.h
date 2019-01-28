#pragma once
#include"AudioCommand.h"
#include"AudioManager.h"

namespace htAudio {

	class PlayCommand : public AudioCommand
	{
	public:
		PlayCommand(OrderFormat fmt);
		~PlayCommand();

		// DLL�������p
		virtual bool Execute();
		
	private:
		// DLL�������p
		bool Play(int source);
	};

}