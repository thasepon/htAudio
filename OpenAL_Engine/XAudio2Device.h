#pragma once

#include<XAudio2.h>

namespace htAudio
{

	class XAudio2Device
	{
	public:
		XAudio2Device();
		~XAudio2Device();

		void* GetDevice() { return XAudioPtr; }


	private:
		void CreateDevice();
		void ReleaseDevice();

		IXAudio2* XAudioPtr;
		IXAudio2MasteringVoice* MasterVoice;



	};

}