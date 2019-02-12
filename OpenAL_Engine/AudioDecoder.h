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
	/// </summary>
	class AudioDecoder
	{
	public:
		~AudioDecoder();	// デストラクタ

		static bool LoadRIFFFormat(AUDIOFILEFORMAT& headerfmt,SoundType audiodata,std::string filepath);		// ファイルフォーマットの取得		
		static bool AudioBufferDecoder(void* buf, AudioData& audiodata,SoundType type, AUDIOFILEFORMAT headerfmt, std::string filepath);	// ファイルのバッファーを取得

	private:
		AudioDecoder();		// コンストラクタ

		static bool RIFFDecoderOgg(std::string filename, AUDIOFILEFORMAT& format);
		static bool RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format);

		static bool BufferDecoderOgg(AudioData& audiodata, std::string filename,bool loopflag, void* buf);	// オーディオバッファーの取得(.wav)
		static bool BufferDecoderWav(AUDIOFILEFORMAT& Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf); // オーディオバッファーの取得(.ogg)

		static unsigned long Mono16WavDecoder(AUDIOFILEFORMAT& Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf);
		// 必要になったら実装します。
		//static bool Streo16WavDecoder(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf);

		// ここにPreloadの用のメモリ配列を入れる？

	};

}