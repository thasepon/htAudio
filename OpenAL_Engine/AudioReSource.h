#pragma once

#include<string>
#include"AudioDecoder.h"
#include<vector>
#include<map>

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

		// --- Buffer系
		void ReadPreLoadAudio();									// プリロードする音声を一気に読み込んで設定する
		void GetAudioBuffer(SoundType Target,void* buf);			// オーディオバッファを取得する
		void ReleaseResource();										// 現在メモリに確保している音源を解放します
		
		// --- Fotmat系
		void ReadCueFormatData();	// 作成したjsonデータを読み込んで保持する
		AudioCue GetFormatData(int CueId);		// 読み込んだCueデータを取得する
		AudioCue GetFormatData(std::string CueName);		// 読み込んだCueデータを取得する
		void ReleaseFormatData();	// 読み込んだjsonデータを削除する

	private:
		// 読みこんだファイル情報の保存用map
		std::vector<AudioCue> Audioresourcelist;

		// Buffer情報の保存 <AuidoID,Buffer>
		std::map<int,int16_t*> BufferMap;

	};

}