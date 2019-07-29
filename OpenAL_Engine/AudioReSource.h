#pragma once

#include<string>
#include"AudioDecoder.h"
#include<vector>
#include<map>
#include<memory>

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
		void ReadPreLoadAudio();							// プリロードする音声を一気に読み込んで設定する
		void GetAudioBuffer(SoundType Target, long* buf);	// オーディオバッファを取得する
		void ReleaseResource();								// 現在メモリに確保している音源を解放します
		
		// --- Fotmat系
		void ReadCueFormatData();							// 作成したjsonデータを読み込んで保持する
		AudioCue GetFormatData(int CueId);					// 読み込んだCueデータを取得する
		AudioCue GetFormatData(std::string CueName);		// 読み込んだCueデータを取得する
		void ReleaseFormatData();							// 読み込んだjsonデータを削除する

	private:
		std::vector<AudioCue> Audioresourcelist;			// 全ファイルのファイル情報を取得
		std::map<int,long*> BufferMap;						// PreloadBuffer情報の保存 <AuidoID,Buffer>
	};

}