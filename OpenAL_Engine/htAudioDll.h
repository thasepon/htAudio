#pragma once

using namespace htAudio;

#include"AudioManager.h"

#include"OpenAL\OpenAlCore\OpenALDevice.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"
#include"OpenAL/AudioListener/AudioListener.h"

/// <summary>
/// dll�֐�����
/// </summary>
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	// �f�o�C�X
	OpenALDevice* __stdcall htaCreateDevice();
	void __stdcall htaDeleteDevice(OpenALDevice* Instance);

	// �}�l�[�W���[
	AudioManager* __stdcall htaCreateManager();
	void __stdcall htaDeleteManager(AudioManager* Instance);

	// Listener�̋@�\
	AudioListener* __stdcall htaListenerCreate();
	void __stdcall htaListenerDelete(AudioListener* Instance);
	void __stdcall htaListenerPosition(AudioListener* Instance, double x, double y, double z);
	void __stdcall htaListenerPositionArray(AudioListener* Instance, double Pos[3]);
	void __stdcall htaListenerVelocity(AudioListener* Instance, double x, double y, double z);
	void __stdcall htaListenerVelocityArray(AudioListener* Instance, double Pos[3]);
	void __stdcall htaListenerOrientation(AudioListener* Instance, double AtVec[3], double UpVec[3]);
	void __stdcall htaListenerOrientationArray(AudioListener* Instance, double AtOrient[6]);

	// Speaker�֌W
	void* __stdcall htaSpeakerCreate(AudioManager* mgtPtr);
	void* __stdcall htaSpeakerCreateI(AudioManager* mgtPtr,uint16_t id);
	void* __stdcall htaSpeakerCreateN(AudioManager* mgtPtr,wchar_t* soundname);
	void __stdcall htaSpeakerDeleteI(AudioManager* mgtPtr, int Numb);
	void __stdcall htaSpeakerDeleteP(AudioManager* mgtPtr, AudioSpeaker* speakerPtr);
	void __stdcall htaSetAudioSourceI(AudioSpeaker* speakerPtr, uint16_t id);
	void __stdcall htaSetAudioSourceN(AudioSpeaker* speakerPtr, wchar_t* soundname);
	void __stdcall htaSetMaterialName(AudioSpeaker* speakerPtr, wchar_t* matereialname);
	bool __stdcall PlayI(AudioManager* ptr ,int speakerId);
	bool __stdcall PlayIL(AudioManager* ptr, int speakerId,int laytency);
	bool __stdcall PlayP(AudioManager* ptr ,AudioSpeaker* speakerPtr);
	bool __stdcall PlayPL(AudioManager* ptr,AudioSpeaker* speakerPtr, int laytency);
	bool __stdcall StopI(AudioManager* ptr, int speakerId);
	bool __stdcall StopIL(AudioManager* ptr, int speakerId, int laytency);
	bool __stdcall StopP(AudioManager* ptr, AudioSpeaker* speakerPtr);
	bool __stdcall StopPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency);
	bool __stdcall PauseI(AudioManager* ptr, int speakerId);
	bool __stdcall PauseIL(AudioManager* ptr, int speakerId, int laytency);
	bool __stdcall PauseP(AudioManager* ptr, AudioSpeaker* speakerPtr);
	bool __stdcall PausePL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency);

	// �G�t�F�N�g����
	// �G�t�F�N�g�ɂ�TAG������̂ł���𑀍삷�镨���K�v

#ifdef __cplusplus
}
#endif