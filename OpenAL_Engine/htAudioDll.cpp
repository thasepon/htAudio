#include"htAudioDll.h"

#include"PlayOrder.h"
#include"AudioData.h"

#include<uchar.h>
#include<codecvt>
#include<string>

/// <summary>
/// ���O�ł̃X�s�[�J�[�̐���������
/// </summary>
/// <param name="mgtPtr">AudioMagr�̃|�C���^���쐬</param>
/// <param name="soundname">Cue�l�[��</param>
/// <returns>�쐬����SpeakerPointer</returns>
void* htaSpeakerCreateN(AudioManager* mgtPtr, wchar_t* soundname)
{
	std::string path, name, mat;

	name = wide_to_multi_capi(soundname);
	
	AudioSpeaker* _speakerPtr = new AudioSpeaker(name);
	uint16_t _id = _speakerPtr->GetSpeakerNumb();
	mgtPtr->AddSpeaker(_id,_speakerPtr);

	return _speakerPtr;
}

/// <summary>
/// ID�ŃX�s�[�J�[�𐶐�����
/// </summary>
/// <param name="mgtPtr">AudioMagr�̃|�C���^���쐬</param>
/// <param name="id">Cue�l�[��</param>
/// <returns>�쐬����SpeakerPointer</returns>
void* htaSpeakerCreateI(AudioManager* mgtPtr,uint16_t id)
{
	AudioSpeaker* _speakerPtr = new AudioSpeaker(id);
	uint16_t _id = _speakerPtr->GetSpeakerNumb();
	mgtPtr->AddSpeaker(_id, _speakerPtr);

	return _speakerPtr;
}

/// <summary>
/// �o�^���Ă���X�s�[�J�[�̍폜
/// </summary>
/// <param name="mgtPtr"></param>
/// <param name="Numb"></param>
void  htaSpeakerDeleteN(AudioManager* mgtPtr, int Numb)
{
	mgtPtr->RemoveSpeaker(Numb);
}

/// <summary>
/// �o�^���Ă���X�s�[�J�[�̍폜
/// </summary>
/// <param name="mgtPtr"></param>
/// <param name="Numb"></param>
void  htaSpeakerDeleteP(AudioManager* mgtPtr, AudioSpeaker* speakerPtr)
{
	mgtPtr->RemoveSpeaker(speakerPtr);
}

bool  Play(AudioManager* ptr, int speakerId)
{
	PlayOrder::SetOrder(ptr, speakerId);
	return true;
}

bool PlayL(AudioManager* ptr, int speakerId, int laytency)
{
	PlayOrder::SetOrder(ptr, speakerId , laytency );
	return true;
}

bool  Stop(int speakerId)
{
	alSourceStop(speakerId);
	return true;
}

bool  Pause(int speakerId)
{
	alSourcePause(speakerId);
	return true;
}

AudioListener* htaListenerCreate()
{
	return new AudioListener();
}

void htaListenerDelete(AudioListener* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}

	delete Instance;
}

void htaListenerPosition(AudioListener* Instance, float x, float y, float z)
{
	Instance->Setposition(x, y, z);
}

void htaListenerPositionArray(AudioListener* Instance, float Pos[3])
{
	Instance->Setposition(Pos);
}

void htaListenerVelocity(AudioListener* Instance, float x, float y, float z)
{
	Instance->SetVelocity(x, y, z);
}

void htaListenerVelocityArray(AudioListener* Instance, float vec[3])
{
	Instance->SetVelocity(vec);
}

void htaListenerOrientation(AudioListener* Instance, float AtVec[3], float UpVec[3])
{
	Instance->SetOrientation(AtVec, UpVec);
}

void htaListenerOrientationArray(AudioListener* Instance, float AtOrient[6])
{
	Instance->SetOrientation(AtOrient);
}

OpenALDevice* htaCreateDevice()
{
	return new OpenALDevice();
}

void htaDeleteDevice(OpenALDevice* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}

	delete Instance;
}


AudioManager* htaCreateManager()
{
	return new AudioManager();
}

void htaDeleteManager(AudioManager* instance)
{
	if (instance == nullptr)
	{
		return;
	}

	delete instance;
}

/// <summary>
/// 3DAudio�̋@�\��On�ɂ���
/// �ʒu���A�������A���x�����|�C���^�œn���Ď����X�V
/// </summary>
void htaAddI3DAudio(AudioManager* mgtPtr, int speakerId, I3DAudioInfo* info)
{
	I3DAudio* i3deffect = new I3DAudio(speakerId,info);
	mgtPtr->AddEffect(i3deffect,speakerId);
}

/// <summary>
/// 3DAudio�̃R�[�����@�\��On�ɂ���
/// �C���i�[�A���O���A�A�E�^�[�A���O���A�A�E�^�[�Q�C����ݒ肷��
/// </summary>
void htaAddCone(AudioManager* mgtPtr, int speakerId, float innerangle, float outerangle, float outergain)
{
	ConeState* conestate = new ConeState(speakerId);
	conestate->SetConeInnerAngle(innerangle);
	conestate->SetConeOuterAngle(outerangle);
	conestate->SetConeOuterGain(outergain);
	mgtPtr->AddEffect(conestate,speakerId);
}

void htaSpeakerSetConeOuterGain(int speakerId, float val)
{
	alSourcef(speakerId, AL_CONE_OUTER_GAIN, val);
}

float htaSpeakerGetConeOuterGain(int speakerId)
{
	float val;
	alGetSourcef(speakerId, AL_CONE_OUTER_GAIN, &val);
	return val;
}

void htaSpeakerSetConeInnerAngle(int speakerId, float val)
{
	alSourcef(speakerId, AL_CONE_INNER_ANGLE, val);
}

float htaSpeakerGetConeInnerAngle(int speakerId)
{
	float val;
	alGetSourcef(speakerId, AL_CONE_INNER_ANGLE, &val);
	return val;
}

void htaSpeakerSetConeOuterAngle(int speakerId, float val)
{
	alSourcef(speakerId, AL_CONE_OUTER_ANGLE, val);
}

float htaSpeakerGetConeOuterAngle(int speakerId)
{
	float val;
	alGetSourcef(speakerId, AL_CONE_OUTER_ANGLE, &val);
	return val;
}

/// <summary>
/// ���o�[���̋@�\��On�ɂ���
/// 
/// </summary>
void htaAddReverb(AudioManager* mgtPtr, int speakerId, REVERB_INFO* info)
{
	ReverbEffects* effect = new ReverbEffects(speakerId);
	effect->SetInfo(info);
	mgtPtr->AddEffect(effect,speakerId);
}