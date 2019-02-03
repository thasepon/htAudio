#include"htAudioDll.h"

#include"OpenAL/AudioSpeaker/AudioSpeaker.h"
#include"OpenAL\OpenAlCore\OpenALDevice.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"

#include"PlayOrder.h"
#include"StopOrder.h"
#include"PauseOrder.h"
#include"AudioData.h"

#include<uchar.h>
#include<codecvt>
#include<string>

namespace htAudio
{

	// ================= 機能関数 ======================= //

	/// <summary>
	/// wstring型をstring型に変換する
	/// </summary>
	/// <param name="src"></param>
	/// <returns></returns>
	std::string wide_to_multi_capi(std::wstring const& src)
	{
		std::size_t converted{};
		std::vector<char> dest(src.size() * sizeof(wchar_t) + 1, '\0');
		if (::_wcstombs_s_l(&converted, dest.data(), dest.size(), src.data(), _TRUNCATE, ::_create_locale(LC_ALL, "jpn")) != 0) {
			throw std::system_error{ errno, std::system_category() };
		}
		dest.resize(std::char_traits<char>::length(dest.data()));
		dest.shrink_to_fit();
		return std::string(dest.begin(), dest.end());
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

	void ExecOrder(AudioManager* Instance)
	{
		Instance->ExecOrderCmd();
	}

	void htaDeleteManager(AudioManager* instance)
	{
		if (instance == nullptr)
		{
			return;
		}

		delete instance;
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


	// ========================================= Speaker ====================================== //

	/// <summary>
	/// スピーカーの生成をします。
	/// </summary>
	/// <param name="mgtPtr"></param>
	/// <returns></returns>
	AudioSpeaker* htaSpeakerCreate(AudioManager* mgtPtr)
	{
		AudioSpeaker* _speakerPtr = new AudioSpeaker();
		uint16_t _id = _speakerPtr->GetSpeakerNumb();
		mgtPtr->GetSpeakerManagerPtr()->AddSpeaker(_speakerPtr);
		return _speakerPtr;
	}

	/// <summary>
	/// 名前でのスピーカーの生成をする
	/// </summary>
	/// <param name="mgtPtr">AudioMagrのポインタを作成</param>
	/// <param name="soundname">Cueネーム</param>
	/// <returns>作成したSpeakerPointer</returns>
	AudioSpeaker* htaSpeakerCreateN(AudioManager* mgtPtr, wchar_t* soundname)
	{
		std::string path, name, mat;

		name = wide_to_multi_capi(soundname);

		AudioSpeaker* _speakerPtr = new AudioSpeaker(name);
		uint16_t _id = _speakerPtr->GetSpeakerNumb();
		mgtPtr->GetSpeakerManagerPtr()->AddSpeaker( _speakerPtr);

		return _speakerPtr;
	}

	/// <summary>
	/// IDでスピーカーを生成する
	/// </summary>
	/// <param name="mgtPtr">AudioMagrのポインタを作成</param>
	/// <param name="id">Cueネーム</param>
	/// <returns>作成したSpeakerPointer</returns>
	AudioSpeaker* htaSpeakerCreateI(AudioManager* mgtPtr, uint16_t id)
	{
		AudioSpeaker* _speakerPtr = new AudioSpeaker(id);
		uint16_t _id = _speakerPtr->GetSpeakerNumb();
		mgtPtr->GetSpeakerManagerPtr()->AddSpeaker( _speakerPtr);

		return _speakerPtr;
	}

	/// <summary>
	/// 登録してあるスピーカーの削除
	/// </summary>
	/// <param name="mgtPtr"></param>
	/// <param name="Numb"></param>
	void  htaSpeakerDelete(AudioManager* mgtPtr, AudioSpeaker* speakerptr)
	{
		mgtPtr->GetSpeakerManagerPtr()->RemoveSpeaker(speakerptr);
		speakerptr = nullptr;
	}

	void htaSetAudioSourceI(AudioSpeaker* speakerPtr, uint16_t id)
	{
		speakerPtr->SetAudioSorce(id);
	}

	void htaSetAudioSourceN(AudioSpeaker* speakerPtr, wchar_t* soundname)
	{
		std::string name;
		name = wide_to_multi_capi(soundname);
		speakerPtr->SetAudioSorce(name);
	}

	void htaSetMaterialName(AudioSpeaker* speakerPtr, wchar_t* matereialname)
	{
		std::string name;
		name = wide_to_multi_capi(matereialname);
		speakerPtr->SetMaterial(name);
	}

	bool  PlayI(AudioManager* ptr, int speakerId)
	{
		PlayOrder::SetPlayOrder(ptr, speakerId);
		return true;
	}

	bool PlayIL(AudioManager* ptr, int speakerId, int laytency)
	{
		PlayOrder::SetPlayOrder(ptr, speakerId, laytency);
		return true;
	}

	bool  PlayP(AudioManager* ptr, AudioSpeaker* speakerPtr)
	{
		PlayOrder::SetPlayOrder(ptr, speakerPtr->GetSpeakerNumb());
		return true;
	}

	bool PlayPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency)
	{
		PlayOrder::SetPlayOrder(ptr, speakerPtr->GetSpeakerNumb(), laytency);
		return true;
	}

	bool  StopI(AudioManager* ptr, int speakerId)
	{
		StopOrder::SetStopOrder(ptr, speakerId);
		return true;
	}

	bool  StopIL(AudioManager* ptr, int speakerId, int laytency)
	{
		StopOrder::SetStopOrder(ptr, speakerId, laytency);
		return true;
	}

	bool  StopP(AudioManager* ptr, AudioSpeaker* speakerPtr)
	{
		StopOrder::SetStopOrder(ptr, speakerPtr->GetSpeakerNumb());
		return true;
	}

	bool  StopPL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency)
	{
		PauseOrder::SetPauseOrder(ptr, speakerPtr->GetSpeakerNumb(), laytency);
		return true;
	}

	bool  PauseI(AudioManager* ptr, int speakerId)
	{
		PauseOrder::SetPauseOrder(ptr, speakerId);
		return true;
	}

	bool  PauseIL(AudioManager* ptr, int speakerId, int laytency)
	{
		PauseOrder::SetPauseOrder(ptr, speakerId, laytency);
		return true;
	}

	bool  PauseP(AudioManager* ptr, AudioSpeaker* speakerPtr)
	{
		PauseOrder::SetPauseOrder(ptr, speakerPtr->GetSpeakerNumb());
		return true;
	}

	bool  PausePL(AudioManager* ptr, AudioSpeaker* speakerPtr, int laytency)
	{
		PauseOrder::SetPauseOrder(ptr, speakerPtr->GetSpeakerNumb(), laytency);
		return true;
	}

	// ========================================= セットスピーカー ====================================== //

	void SetExeDirectory(wchar_t* soundname)
	{
		wstring wstr = soundname;
		ExeDirectory = wide_to_multi_capi(wstr);
	}
	

}