#pragma once

#include<string>
#include"AudioDecoder.h"
#include<vector>

namespace htAudio
{
	/// <summary>
	/// wavやoggのオーディオの管理をするクラス
	/// ここを経由してリソースを取得する
	/// </summary>
	class AudioReSource
	{
	public:
		AudioReSource();
		~AudioReSource();
		void ReadPreLoadAudio();	// プリロードする音声を一気に読み込んで設定する
		void GetAudioBuffer(std::string name, AUDIOFILEFORMAT* fmt, std::list<SoundType>* type, AudioCue* cue, AudioData* data,void* buf);			// オーディオバッファを取得する
		void GetAudioBuffer(int Id, AUDIOFILEFORMAT* fmt, std::list<SoundType>* type, AudioCue* cue, AudioData* data, void* buf);			// オーディオバッファを取得する
		void ReleaseResource();			// 現在メモリに確保している音源を解放します
		
	private:
		// 読みこんだファイル情報の保存用map
		std::vector<ResourceData> Audioresourcelist;


	};

}