#pragma once

#include<string>
#include"AudioDecoder.h"
#include<vector>

namespace htAudio
{
	// リソース使いまわしに必要なデータ
	struct ResourceData
	{
		AUDIOFILEFORMAT fmt;
		void* DataBuffer;
	};

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
		void GetAudioBuffer(std::string name);			// オーディオバッファを取得する
		void GetAudioBuffer(int Id);			// オーディオバッファを取得する
		void ReleaseResource();			// 現在メモリに確保している音源を解放します
		
	private:
		// 読みこんだファイルの保存用map
		std::vector<ResourceData> AudioresourceMap;

	};

}