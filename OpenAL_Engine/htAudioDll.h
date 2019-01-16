#pragma once

#include"Definclude.h"

#include"OpenAL/AudioSpeaker/AudioSpeaker.h"
#include"OpenAL/AudioListener/AudioListener.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

#include"I3DAudio.h"
#include"ConeState.h"
#include"ReverbEffects.h"
#include"AudioManager.h"

using namespace htAudio;


/// <summary>
/// dll�֐�����
/// </summary>
extern "C" {

	// �f�o�C�X�AManager
	UNITY_INTERFACE_EXPORT OpenALDevice* UNITY_INTERFACE_API htaCreateDevice();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaDeleteDevice(OpenALDevice* Instance);
	UNITY_INTERFACE_EXPORT AudioManager* UNITY_INTERFACE_API htaCreateManager();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaDeleteManager(AudioManager* Instance);

	// Listener�̋@�\
	UNITY_INTERFACE_EXPORT AudioListener* UNITY_INTERFACE_API htaListenerCreate();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerDelete(AudioListener*);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPosition(AudioListener* Instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPositionArray(AudioListener* Instance, float Pos[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocity(AudioListener* Instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocityArray(AudioListener* Instance, float Pos[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientation(AudioListener* Instance, float AtVec[3], float UpVec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientationArray(AudioListener* Instance, float AtOrient[6]);

	// Speaker�֌W
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreate(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname, wchar_t* material);
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreateID(AudioManager* mgtPtr, wchar_t* filepath, uint16_t id);
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreateName(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDelete(AudioManager* mgtPtr, int Numb);
	
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Play(AudioManager* ptr,int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayL(AudioManager* ptr,int speakerId,int laytency);

	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Stop(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Pause(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Formatflag(AudioManager* mgtPtr, int speakerId);

	// Effect�̋@�\

	/* 3DAudio�֌W */
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaAddI3DAudio(AudioManager* mgtPtr, int speakerId, I3DAudioInfo* info);

	/* Corn�֌W */
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaAddCone(AudioManager* mgtPtr, int speakerId, float innerangle, float outerangle, float outergain);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterGain(int speakerId, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterGain(int speakerId);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeInnerAngle(int speakerId, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeInnerAngle(int speakerId);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterAngle(int speakerId, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterAngle(int speakerId);

	/* Reverb�֌W */
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaAddReverb(AudioManager* mgtPtr, int speakerId, REVERB_INFO* info);

}