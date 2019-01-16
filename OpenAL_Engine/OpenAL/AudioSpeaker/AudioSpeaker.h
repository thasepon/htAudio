#pragma once

#include"../../AudioData.h"
#include"../../AudioReSource.h"
#include"../../AudioEffects.h"

#include"../../PlayCommand.h"
#include"../../StopCommand.h"
#include"../../PauseCommand.h"

#include<string>
#include<memory>
#include<array>
#include<functional>
#include<future>

#include<AL/efx.h>
#include<AL/efx-creative.h>


namespace htAudio
{
	using namespace std;

	/// <summary>
	/// サウンドの再生用クラス
	/// サウンド再生の窓口クラス
	/// </summary>
	class AudioSpeaker
	{
	public:
		// 情報指定
		AudioSpeaker(string filepath, string SoundName, string material);
		// ID指定
		AudioSpeaker(string filepath, int id);
		//指定なし
		AudioSpeaker(string filepath, string SoundName);
		
		~AudioSpeaker();// デスト

		void StopUpdate();

		bool AddEffects(AudioEffects* effect);

		ALuint GetSpeakerNumb() { return Source; }
		bool Update();									// 更新

	private:
		bool SetBuffer(ALuint Buf);						// バッファの設定
		void Init();									// 共通初期化処理

		bool Successinit = false;						// 初期化成功フラグ
		bool LoopFlag = true;							// updateloopフラグ

		std::shared_ptr<AudioResources> AudioSource;	// オーディオ情報
		
		std::string UseMaterialAtt;						// マテリアルの設定
		std::string Filepath;							// ファイルパス

		// OpenAL情報
		std::array<ALuint,2> Buffers;					// バッファの設定
		ALuint Source;									// Sourceの設定
		
		std::vector<AudioEffects*> EffectSlot;		// エフェクトスロット
		
		ALfloat Volume;								// ボリューム

		AudioCommand* BufferCommand;	// バッファ回りのコマンド
	};

}