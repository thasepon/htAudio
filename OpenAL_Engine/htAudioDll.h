#pragma once

using namespace htAudio;

#include"AudioManager.h"
#include"Definclude.h"
#include"OpenAL\OpenAlCore\OpenALDevice.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"
#include"OpenAL/AudioListener/AudioListener.h"

/// <summary>
/// dll関数部分
/// </summary>
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	// デバイス
	UNITY_INTERFACE_EXPORT OpenALDevice* __stdcall htaCreateDevice();
	UNITY_INTERFACE_EXPORT void __stdcall htaDeleteDevice(OpenALDevice* Instance);

	// マネージャー
	UNITY_INTERFACE_EXPORT AudioManager* __stdcall htaCreateManager();
	UNITY_INTERFACE_EXPORT void __stdcall htaDeleteManager(AudioManager* Instance);

	// Listenerの機能
	UNITY_INTERFACE_EXPORT AudioListener* __stdcall htaListenerCreate();
	UNITY_INTERFACE_EXPORT void __stdcall htaListenerDelete(AudioListener* Instance);
	UNITY_INTERFACE_EXPORT void __stdcall htaListenerPosition(AudioListener* Instance, double x, double y, double z);
	UNITY_INTERFACE_EXPORT void __stdcall htaListenerPositionArray(AudioListener* Instance, double Pos[3]);
	UNITY_INTERFACE_EXPORT void __stdcall htaListenerVelocity(AudioListener* Instance, double x, double y, double z);
	UNITY_INTERFACE_EXPORT void __stdcall htaListenerVelocityArray(AudioListener* Instance, double Pos[3]);
	UNITY_INTERFACE_EXPORT void __stdcall htaListenerOrientation(AudioListener* Instance, double AtVec[3], double UpVec[3]);
	UNITY_INTERFACE_EXPORT void __stdcall htaListenerOrientationArray(AudioListener* Instance, double AtOrient[6]);

	// Speaker関係
	UNITY_INTERFACE_EXPORT void* __stdcall htaSpeakerCreate(AudioManager* mgtPtr);
	UNITY_INTERFACE_EXPORT void* __stdcall htaSpeakerCreateI(AudioManager* mgtPtr,uint16_t id);
	UNITY_INTERFACE_EXPORT void* __stdcall htaSpeakerCreateN(AudioManager* mgtPtr,wchar_t* soundname);
	UNITY_INTERFACE_EXPORT void __stdcall htaSpeakerDeleteI(AudioManager* mgtPtr, int Numb);
	UNITY_INTERFACE_EXPORT void __stdcall htaSpeakerDeleteP(AudioManager* mgtPtr, AudioSpeaker* speakerPtr);
	UNITY_INTERFACE_EXPORT void __stdcall htaSetAudioSourceI(AudioSpeaker* speakerPtr, uint16_t id);
	UNITY_INTERFACE_EXPORT void __stdcall htaSetAudioSourceN(AudioSpeaker* speakerPtr, wchar_t* soundname);
	UNITY_INTERFACE_EXPORT void __stdcall htaSetMaterialName(AudioSpeaker* speakerPtr, wchar_t* matereialname);
	UNITY_INTERFACE_EXPORT bool __stdcall PlayI(AudioManager* ptr ,int speakerId);
	UNITY_INTERFACE_EXPORT bool __stdcall PlayIL(AudioManager* ptr, int speakerId,int laytency);
	UNITY_INTERFACE_EXPORT bool __stdcall PlayP(AudioManager* ptr ,AudioSpeaker* speakerPtr);
	UNITY_INTERFACE_EXPORT bool __stdcall PlayPL(AudioManager* ptr,AudioSpeaker* speakerPtr, int laytency);
	UNITY_INTERFACE_EXPORT bool __stdcall StopI(AudioManager* ptr, int speakerId);
	UNITY_INTERFACE_EXPORT bool __stdcall StopIL(AudioManager* ptr, int speakerId, int laytency);
	UNITY_INTERFACE_EXPORT bool __stdcall StopP(AudioManager* ptr, AudioSpeaker* speakerPtr);
	UNITY_INTERFACE_EXPORT bool __stdcall StopPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency);
	UNITY_INTERFACE_EXPORT bool __stdcall PauseI(AudioManager* ptr, int speakerId);
	UNITY_INTERFACE_EXPORT bool __stdcall PauseIL(AudioManager* ptr, int speakerId, int laytency);
	UNITY_INTERFACE_EXPORT bool __stdcall PauseP(AudioManager* ptr, AudioSpeaker* speakerPtr);
	UNITY_INTERFACE_EXPORT bool __stdcall PausePL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency);

	// エフェクト操作
	// エフェクトにもTAGがあるのでそれを操作する物が必要

#ifdef __cplusplus
}
#endif