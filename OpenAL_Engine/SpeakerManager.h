#pragma once

#include<list>

#include"AudioData.h"
#include"OpenAL\AudioSpeaker\AudioSpeaker.h"

namespace htAudio
{
	/// <summary>
	/// スピーカーの一括変更に使用するクラス
	/// </summary>
	class SpeakerManager
	{
	public:
		SpeakerManager();
		~SpeakerManager();

		void AddSpeaker(AudioSpeaker* speakerptr);		// スピーカーの追加
		void RemoveSpeaker(AudioSpeaker* speakerptr);	// スピーカーの削除
		void AllDeleteSpeaker();						// スピーカーの全削除

		void SpeakerUpdate();							// 登録スピーカの更新

		void ControlVolume(VOLUMETYPE type,double value);	// ボリュームの一括変更

	private:
		std::list<AudioSpeaker*> SpeakerList;	// AudioSpeakerを一括変更かけたりする時に使用するlist
		std::array<double, VOLUMETYPE::MAX_VOLUMETYPE> VolumeArray; // 各種ボリュームの配列

	};

}