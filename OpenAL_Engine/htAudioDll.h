#pragma once

#include"Definclude.h"
#include"AudioManager.h"
#include"OpenAL\OpenAlCore\OpenALDevice.h"
#include"OpenAL/AudioListener/AudioListener.h"


namespace htAudio
{
	/// <summary>
	/// dll関数部分
	/// </summary>
#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus

		// デバイス
		UNITY_INTERFACE_EXPORT OpenALDevice* UNITY_INTERFACE_API htaCreateDevice();
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaDeleteDevice(OpenALDevice* Instance);

		// マネージャー
		UNITY_INTERFACE_EXPORT AudioManager* UNITY_INTERFACE_API htaCreateManager();
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API ExecOrder(AudioManager* Instance);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaDeleteManager(AudioManager* Instance);

		// Listenerの機能
		UNITY_INTERFACE_EXPORT AudioListener* UNITY_INTERFACE_API htaListenerCreate();
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerDelete(AudioListener* Instance);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPosition(AudioListener* Instance, double x, double y, double z);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPositionArray(AudioListener* Instance, double Pos[3]);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocity(AudioListener* Instance, double x, double y, double z);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocityArray(AudioListener* Instance, double Pos[3]);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientation(AudioListener* Instance, double AtVec[3], double UpVec[3]);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientationArray(AudioListener* Instance, double AtOrient[6]);

		// Speaker関係
		UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreate(AudioManager* mgtPtr);
		UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateI(AudioManager* mgtPtr, uint16_t id);
		UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateN(AudioManager* mgtPtr, wchar_t* soundname);
		
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDelete(AudioManager* mgtPtr, AudioSpeaker* speakerPtr);
		
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSetAudioSourceI(AudioSpeaker* speakerPtr, uint16_t id);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSetAudioSourceN(AudioSpeaker* speakerPtr, wchar_t* soundname);
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSetMaterialName(AudioSpeaker* speakerPtr, wchar_t* matereialname);
		
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayI(AudioManager* ptr, int speakerId);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayIL(AudioManager* ptr, int speakerId, int laytency);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayP(AudioManager* ptr, AudioSpeaker* speakerPtr);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency);
		
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopI(AudioManager* ptr, int speakerId);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopIL(AudioManager* ptr, int speakerId, int laytency);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopP(AudioManager* ptr, AudioSpeaker* speakerPtr);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency);
		
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PauseI(AudioManager* ptr, int speakerId);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PauseIL(AudioManager* ptr, int speakerId, int laytency);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PauseP(AudioManager* ptr, AudioSpeaker* speakerPtr);
		UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PausePL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency);

		// ファイルパスの設定
		UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetExeDirectory(wchar_t* soundname);

		// エフェクト操作
		// エフェクトにもTAGがあるのでそれを操作する物が必要

#ifdef __cplusplus
	}
#endif

}