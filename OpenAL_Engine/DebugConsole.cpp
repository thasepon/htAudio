#include "DebugConsole.h"

namespace htAudio
{

	DebugConsole::DebugConsole()
	{
		CreateConcole();
	}


	DebugConsole::~DebugConsole()
	{
	}

	void DebugConsole::CreateConcole()
	{
		FILE* fp;

		AllocConsole();

		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);

	}



}