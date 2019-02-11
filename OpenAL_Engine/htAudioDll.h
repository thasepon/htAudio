#pragma once


#include"Definclude.h"
#include"AudioManager.h"
#include"OpenAL\OpenAlCore\OpenALDevice.h"
#include"OpenAL/AudioListener/AudioListener.h"

using namespace htAudio;

/// <summary>
/// dll�֐�����
/// </summary>
extern "C" {

	// ��������
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API DeleteInstance();

	// �f�o�C�X
	UNITY_INTERFACE_EXPORT OpenALDevice* UNITY_INTERFACE_API htaCreateDevice();
	
	// �}�l�[�W���[
	UNITY_INTERFACE_EXPORT AudioManager* UNITY_INTERFACE_API htaCreateManager();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API ExecOrder();

	// Listener�̋@�\
	UNITY_INTERFACE_EXPORT AudioListener* UNITY_INTERFACE_API htaListenerCreate();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerDelete(AudioListener* Instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPosition(AudioListener* Instance, double x, double y, double z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPositionArray(AudioListener* Instance, double Pos[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocity(AudioListener* Instance, double x, double y, double z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocityArray(AudioListener* Instance, double Pos[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientation(AudioListener* Instance, double AtVec[3], double UpVec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientationArray(AudioListener* Instance, double AtOrient[6]);

	// Speaker�֌W
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreate();
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateI(uint16_t id);
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateN(wchar_t* soundname);
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDelete(AudioSpeaker* speakerPtr);
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSetAudioSourceI(AudioSpeaker* speakerPtr, uint16_t id);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSetAudioSourceN(AudioSpeaker* speakerPtr, wchar_t* soundname);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSetMaterialName(AudioSpeaker* speakerPtr, wchar_t* matereialname);
	
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayI( int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayIL(int speakerId, int laytency);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayP( AudioSpeaker* speakerPtr);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PlayPL(AudioSpeaker* speakerPtr, int laytency);
	
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopI( int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopIL(int speakerId, int laytency);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopP( AudioSpeaker* speakerPtr);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API StopPL(AudioSpeaker* speakerPtr, int laytency);
	
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PauseI( int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PauseIL(int speakerId, int laytency);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PauseP( AudioSpeaker* speakerPtr);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API PausePL(AudioSpeaker* speakerPtr, int laytency);

	// �t�@�C���p�X�̐ݒ�
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetExeDirectory(wchar_t* soundname);

	// �G�t�F�N�g����
	// �G�t�F�N�g�ɂ�TAG������̂ł���𑀍삷�镨���K�v

}