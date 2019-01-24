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

		static bool LoadRIFFFormat(AudioResources& source, int soundTypeNumber);		// ファイルフォーマットの取得		
		static bool AudioBufferDecoder(AudioResources& source,int soundTypeNumber);	// ファイルのバッファーを取得

	private:
		AudioDecoder();		// コンストラクタ

		static bool RIFFDecoderOgg(std::string filename, AUDIOFILEFORMAT& format);
		static bool RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format);

		static bool BufferDecoderOgg(AudioData& audiodata, void* buf);	// オーディオバッファーの取得(.wav)
		static bool BufferDecoderWav(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf); // オーディオバッファーの取得(.ogg)

		static bool Mono16WavDecoder(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf);
		// 必要になったら実装します。
		//static bool Streo16WavDecoder(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf);
	};

}