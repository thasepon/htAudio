#pragma once

#include<string>
#include<map>
#include"AudioDecoder.h"

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

		void PreLoad(std::string name);	// メモリにのせて再利用します
		void PreLoad(int Id);			// メモリにのせて再利用します
		void StreamLoad(std::string);	// メモリに分割してのせて再生後は解放します
		void StreamLoad(int Id);	// メモリに分割してのせて再生後は解放します
		
		void ReleaseResource();	// 現在メモリに確保している音源を解放します
		
	private:
		// 読みこんだファイルの保存用map
		ResourceData* AudioresourceMap;

	};

}