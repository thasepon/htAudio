#include"htAudioDll.h"

#include"AudioData.h"

#include"PlayOrder.h"
#include"StopOrder.h"
#include"PauseOrder.h"

#include<uchar.h>
#include<codecvt>
#include<string>

// ========================================= Speaker ====================================== //

/// <summary>
/// 名前でのスピーカーの生成をする
/// </summary>
/// <param name="mgtPtr">AudioMagrのポインタを作成</param>
/// <param name="soundname">Cueネーム</param>
/// <returns>作成したSpeakerPointer</returns>
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
/// IDでスピーカーを生成する
/// </summary>
/// <param name="mgtPtr">AudioMagrのポインタを作成</param>
/// <param name="id">Cueネーム</param>
/// <returns>作成したSpeakerPointer</returns>
void* htaSpeakerCreateI(AudioManager* mgtPtr,uint16_t id)
{
	AudioSpeaker* _speakerPtr = new AudioSpeaker(id);
	uint16_t _id = _speakerPtr->GetSpeakerNumb();
	mgtPtr->AddSpeaker(_id, _speakerPtr);

	return _speakerPtr;
}

/// <summary>
/// 登録してあるスピーカーの削除
/// </summary>
/// <param name="mgtPtr"></param>
/// <param name="Numb"></param>
void  htaSpeakerDeleteI(AudioManager* mgtPtr, int Numb)
{
	mgtPtr->RemoveSpeaker(Numb);
}

/// <summary>
/// 登録してあるスピーカーの削除
/// </summary>
/// <param name="mgtPtr"></param>
/// <param name="Numb"></param>
void  htaSpeakerDeleteP(AudioManager* mgtPtr, AudioSpeaker* speakerPtr)
{
	mgtPtr->RemoveSpeaker(speakerPtr);
	speakerPtr = nullptr;
}

bool  PlayI(AudioManager* ptr, int speakerId)
{
	PlayOrder::SetOrder(ptr, speakerId);
	return true;
}

bool PlayIL(AudioManager* ptr, int speakerId, int laytency)
{
	PlayOrder::SetOrder(ptr, speakerId , laytency );
	return true;
}

bool  PlayP(AudioManager* ptr, AudioSpeaker* speakerPtr)
{
	PlayOrder::SetOrder(ptr, speakerPtr->GetSpeakerNumb());
	return true;
}

bool PlayPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency)
{
	PlayOrder::SetOrder(ptr, speakerPtr->GetSpeakerNumb(), laytency);
	return true;
}

bool  StopI(AudioManager* ptr, int speakerId)
{
	StopOrder::SetOrder(ptr, speakerId);
	return true;
}

bool  StopIL(AudioManager* ptr, int speakerId, int laytency)
{
	StopOrder::SetOrder(ptr, speakerId,laytency);
	return true;
}

bool  StopP(AudioManager* ptr, AudioSpeaker* speakerPtr)
{
	StopOrder::SetOrder(ptr, speakerPtr->GetSpeakerNumb());
	return true;
}

bool  StopPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency)
{
	PauseOrder::SetOrder(ptr, speakerPtr->GetSpeakerNumb(), laytency);
	return true;
}

bool  PauseI(AudioManager* ptr, int speakerId)
{
	PauseOrder::SetOrder(ptr, speakerId);
	return true;
}

bool  PauseL(AudioManager* ptr, int speakerId, int laytency)
{
	PauseOrder::SetOrder(ptr, speakerId, laytency);
	return true;
}

bool  PauseP(AudioManager* ptr, AudioSpeaker* speakerPtr)
{
	PauseOrder::SetOrder(ptr, speakerPtr->GetSpeakerNumb());
	return true;
}

bool  PausePL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency)
{
	PauseOrder::SetOrder(ptr, speakerPtr->GetSpeakerNumb(), laytency);
	return true;
}


// =================================== LIstener ===================================== //

/// <summary>
/// リスナーの生成処理
/// </summary>
/// <returns>生成されたリスナーを設定</returns>
AudioListener* htaListenerCreate()
{
	return new AudioListener();
}

/// <summary>
/// リスナーを削除します
/// </summary>
/// <param name="Instance"></param>
void htaListenerDelete(AudioListener* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}

	delete Instance;
}

void htaListenerPosition(AudioListener* Instance, double x, double y, double z)
{
	Instance->Setposition(x, y, z);
}

void htaListenerPositionArray(AudioListener* Instance, double Pos[3])
{
	Instance->Setposition(Pos);
}

void htaListenerVelocity(AudioListener* Instance, double x, double y, double z)
{
	Instance->SetVelocity(x, y, z);
}

void htaListenerVelocityArray(AudioListener* Instance, double vec[3])
{
	Instance->SetVelocity(vec);
}

void htaListenerOrientation(AudioListener* Instance, double AtVec[3], double UpVec[3])
{
	Instance->SetOrientation(AtVec, UpVec);
}

void htaListenerOrientationArray(AudioListener* Instance, double AtOrient[6])
{
	Instance->SetOrientation(AtOrient);
}

// ================================= Device ================================= //

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

// =============================== AudioManager ================================= //

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

