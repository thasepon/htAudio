#include "XAudio2Device.h"


namespace htAudio
{
	XAudio2Device::XAudio2Device()
	{
	}


	XAudio2Device::~XAudio2Device()
	{
	}

	void XAudio2Device::CreateDevice()
	{
		HRESULT hr;
		UINT32 Flags;
		UINT32 DeviceCnt;

		XAudioPtr = nullptr;

		if (FAILED(hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
		{
			return;
		}

		if (FAILED(hr = XAudio2Create(&XAudioPtr, Flags)))
		{
			CoUninitialize();
			return;
		}

		if(FAILED(hr = XAudioPtr->CreateMasteringVoice(&MasterVoice)))
		{
			CoUninitialize();
			return;
		}
	}

	void XAudio2Device::ReleaseDevice()
	{

		MasterVoice->DestroyVoice();

		XAudioPtr->Release();
		delete XAudioPtr;

		CoUninitialize();

	}


}