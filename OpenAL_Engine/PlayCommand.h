#pragma once
#include"AudioCommand.h"
#include"AudioManager.h"

namespace htAudio {

	class PlayCommand : public AudioCommand
	{
	public:
		PlayCommand(OrderFormat fmt);
		~PlayCommand();

		// DLL内処理用
		virtual bool Execute() { return Play(OrderFmt.SourceID); }
		
	private:
		// DLL内処理用
		bool Play(int source);
	};

}