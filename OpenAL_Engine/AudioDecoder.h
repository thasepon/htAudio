#pragma once

#include"AudioData.h"

#ifdef USE_OGG_LIB
#include"vorbis/vorbisfile.h"
#pragma comment(lib,"libvorbisfile_static.lib")
#pragma comment(lib,"libogg_static.lib")
#pragma comment(lib,"libvorbis_static.lib")
#endif // USE_OGG_LIB

namespace htAudio
{
	/// <summary>
	/// 16bitWav音源とOggのデコーダー
	/// 機能関数なのでAllStaticにしてます、singletonでもいいのだけどアクセスが面倒になるのでとりあえずStatic
	/// </summary>
	class AudioDecoder
	{
	public:
		~AudioDecoder();	// デストラクタ

		// headerデコード関数
		static bool LoadRIFFFormat(AUDIOFILEFORMAT& headerfmt,SoundType audiodata,std::string filepath);		// ファイルフォーマットの取得		
		
		// Bufデコード関数
		static bool AudioBufferDecoder(void* buf, AudioData* audiodata,SoundType type, AUDIOFILEFORMAT headerfmt, std::string filepath);	// ファイルのバッファーを取得
		
	private:
		AudioDecoder();		// コンストラクタ

		// header部分のデコーダー
		static bool RIFFDecoderOgg(std::string filename, AUDIOFILEFORMAT& format);
		static bool RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format);

		// Data部分のデコーダー
		static bool BufferDecoderOgg(AUDIOFILEFORMAT Format, std::string filename,bool loopflag, AudioData* audiodata, void* buf);	// オーディオバッファーの取得(.wav)
		static bool BufferDecoderWav(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData* audiodata, void* buf); // オーディオバッファーの取得(.ogg)
		
	};

}