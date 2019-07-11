#include "AudioDecoder.h"

namespace htAudio
{

	AudioDecoder::AudioDecoder()
	{
	}


	AudioDecoder::~AudioDecoder()
	{
	}

	/// <summary>
	/// Ogg,wavファイルのヘッダー部分の読み込み
	/// </summary>
	bool AudioDecoder::LoadRIFFFormat(AUDIOFILEFORMAT& headerfmt, SoundType audiodata, std::string filepath)
	{

		if (audiodata.RIFFType == RIFF_WAV)
		{
			return RIFFDecoderWave(filepath + audiodata.AudioName+".wav", headerfmt);
		}
		else if (audiodata.RIFFType == RIFF_OGG)
		{
			return RIFFDecoderOgg(filepath + audiodata.AudioName+".ogg", headerfmt);
		}

		// 処理なし
		return false;

	}

	bool AudioDecoder::RIFFDecoderOgg(std::string filename, AUDIOFILEFORMAT& format)
	{

#ifdef USE_OGG_LIB
		OggVorbis_File Ovf;

		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Oggファイルオープンの失敗
			printf("ヘッダー情報の読み取りに失敗しました");
			return false;
		}

		vorbis_info* vi = ov_info(&Ovf,-1);

		format.Fmt.FormatType = WAVE_FORMAT_PCM;
		format.Fmt.Channels = vi->channels;
		format.Fmt.SamplesPerSec = vi->rate;
		format.Fmt.BlockSize = vi->channels * 2;
		format.Fmt.BitsPerSample = 16;
		format.Fmt.BytesPerSec = (vi->rate) * (vi->channels * 2);

		return true;
#endif
		return false;

	}

	bool AudioDecoder::RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format)
	{
		FILE* fp;

		fopen_s(&fp, filename.c_str(), "rb");

		// オープン失敗
		if (!fp)
		{
			printf("ヘッダー情報の読み取りに失敗しました");
			return false;
		}

		long offset = 0;

		printf("%sを開きます\n", filename.c_str());

		while (true)
		{
			char chunksignature[4] = { 0 };

			if (fread(chunksignature, 4, 1, fp) == 0)
			{
				break;
			}

			offset += 4;

			if (strncmp(chunksignature, "RIFF ", 4) == 0)
			{
				// RIFFチャンクの読み込み
				strcpy(format.Riff.ChunkID, chunksignature);
				offset += fread(&format.Riff.ChunkSize, 4, 1, fp);
				offset += fread(format.Riff.FormatType, 4, 1, fp);

				printf("RIFF :: %s - %d - %s \n", 
					format.Riff.ChunkID, 
					format.Riff.ChunkSize, 
					format.Riff.FormatType);

			}

			if (strncmp(chunksignature, "fmt ", 4) == 0)
			{
				// fmtチャンクの読み込み
				strcpy(format.Fmt.ChunkID, chunksignature);
				offset += fread(&format.Fmt.ChunkSize, 4, 1, fp);
				offset += fread(&format.Fmt.FormatType, 2, 1, fp);
				offset += fread(&format.Fmt.Channels, 2, 1, fp);
				offset += fread(&format.Fmt.SamplesPerSec, 4, 1, fp);
				offset += fread(&format.Fmt.BytesPerSec, 4, 1, fp);
				offset += fread(&format.Fmt.BlockSize, 2, 1, fp);
				offset += fread(&format.Fmt.BitsPerSample, 2, 1, fp);

				printf("FMT :: %s - %d - %d - %d - %d - %d - %d - %d \n", 
					format.Fmt.ChunkID, 
					format.Fmt.ChunkSize, 
					format.Fmt.FormatType,
					format.Fmt.Channels,
					format.Fmt.SamplesPerSec,
					format.Fmt.BytesPerSec,
					format.Fmt.BlockSize,
					format.Fmt.BitsPerSample);

			}

			if (strncmp(chunksignature, "data", 4) == 0)
			{
				// Dataチャンクの読み込み(ただしDataを除く)
				strcpy(format.Data.ChunkID, chunksignature);
				offset += fread(&format.Data.ChunkSize, 4, 1, fp);

				printf("Data :: %s - %d \n",
					format.Data.ChunkID,
					format.Data.ChunkSize);
			}
		}

		if (format.Data.ChunkSize == 0)
		{
			memcpy(format.Data.ChunkID, "data", 4);
			format.Data.ChunkSize = offset;
		}

		// 音データまでの移動量(特殊情報は考えない)
		format.FirstSampleOffSet = 48;

		fclose(fp);
		
		return true;

	}

	/// <summary>
	/// オーディオバッファー読み込み用の窓口関数
	/// </summary>
	bool AudioDecoder::AudioBufferDecoder(void* buf
		,AudioData& audiodata
		,SoundType type
		, AUDIOFILEFORMAT headerfmt
		, std::string filepath)
	{
		bool loadflag = false;

		// 拡張子の判断
		if (type.RIFFType == RIFF_WAV)
		{
			loadflag = BufferDecoderWav(headerfmt, filepath + type.AudioName + ".wav", type.Loopflag , audiodata, buf);
		}
		else if (type.RIFFType == RIFF_OGG)
		{
			loadflag = BufferDecoderOgg(audiodata, filepath + type.AudioName + ".ogg", type.Loopflag, buf);
		}

		// 処理なし
		return loadflag;
	}

	/// <summary>
	/// Preloadのバッファ読み込み
	/// (一部必要のない引数があったので作成)
	/// </summary>
	/// <param name="buf"></param>
	/// <returns></returns>
	bool AudioDecoder::AudioPreloadBufferDecoder(void* buf
		, SoundType type
		, AUDIOFILEFORMAT headerfmt
		, std::string filepath)
	{
		bool loadflag = false;

		// 拡張子の判断
		if (type.RIFFType == RIFF_WAV)
		{
			PreloadWavDecoder(headerfmt, filepath + type.AudioName + ".wav", type.Loopflag, buf);
		}
		else if (type.RIFFType == RIFF_OGG)
		{
			loadflag = PreloadOggDecoder( filepath + type.AudioName + ".wav", type.Loopflag, buf);
		}
	}


	/// <summary>
	/// バッファーの読み込み(.wav)
	/// </summary>
	/// <param name="buf"></param>
	bool AudioDecoder::BufferDecoderOgg(AudioData& audiodata, std::string filename, bool loopflag, void* buf)
	{
		unsigned long requestsize = audiodata.ReadBufSize;
		int bitstream = 0;
		int readsize = 0;
		UINT comsize = 0;
		OggVorbis_File Ovf;
		
		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Oggファイルオープンの失敗
			printf("サウンドファイルの読み取りに失敗しました");
			return false;
		}

		// 読みこみ部分
		while (1)
		{
			readsize = ov_read(&Ovf, (char*)((char*)buf + comsize), requestsize, 0, 2, 1, &bitstream);
			
			// 末端まで読み込み終了
			if (readsize == 0)
			{
				// ループ処理がある場合は読み込み位置を先頭に戻す。
				if (loopflag == true)
				{
					ov_time_seek(&Ovf,0.0);
					audiodata.TotalreadBufSize = 0;
				}
				else 
				{
					// 動作無し
					break;
				}
			}
			// 今回読みこんだ量を保存
			comsize += readsize;
			
			// 指定量のバッファを取得出来たら終了
			if (comsize >= requestsize)
			{
				break;
			}

			// 一定に達していない場合は残りの分をRequestする
			if ((requestsize - comsize) > 0)
			{
				requestsize -= comsize;
			}

		}
		// 現在の読み込み量を加算
		audiodata.TotalreadBufSize += comsize;
		
		return true;
	}

	unsigned long AudioDecoder::StreamOggDecoder(AudioData& audiodata, std::string filename, bool loopflag, void* buf)
	{
		unsigned long requestsize = audiodata.ReadBufSize;
		int bitstream = 0;
		int readsize = 0;
		UINT comsize = 0;
		OggVorbis_File Ovf;

		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Oggファイルオープンの失敗
			printf("サウンドファイルの読み取りに失敗しました");
			return false;
		}

		// 読みこみ部分
		while (1)
		{
			readsize = ov_read(&Ovf, (char*)((char*)buf + comsize), requestsize, 0, 2, 1, &bitstream);

			// 末端まで読み込み終了
			if (readsize == 0)
			{
				// ループ処理がある場合は読み込み位置を先頭に戻す。
				if (loopflag == true)
				{
					ov_time_seek(&Ovf, 0.0);
					audiodata.TotalreadBufSize = 0;
				}
				else
				{
					// 動作無し
					break;
				}
			}
			// 今回読みこんだ量を保存
			comsize += readsize;

			// 指定量のバッファを取得出来たら終了
			if (comsize >= requestsize)
			{
				break;
			}

			// 一定に達していない場合は残りの分をRequestする
			if ((requestsize - comsize) > 0)
			{
				requestsize -= comsize;
			}

		}
		// 現在の読み込み量を加算
		audiodata.TotalreadBufSize += comsize;
	}

	unsigned long AudioDecoder::PreloadOggDecoder(AudioData& audiodata, std::string filename, bool loopflag, void* buf)
	{
		unsigned long requestsize = audiodata.ReadBufSize;
		int bitstream = 0;
		int readsize = 0;
		UINT comsize = 0;
		OggVorbis_File Ovf;

		if (ov_fopen(filename.c_str(), &Ovf))
		{
			// Oggファイルオープンの失敗
			printf("サウンドファイルの読み取りに失敗しました");
			return false;
		}

		// 読みこみ部分
		while (1)
		{
			readsize = ov_read(&Ovf, (char*)((char*)buf + comsize), requestsize, 0, 2, 1, &bitstream);

			// 末端まで読み込み終了
			if (readsize == 0)
			{
				// ループ処理がある場合は読み込み位置を先頭に戻す。
				if (loopflag == true)
				{
					ov_time_seek(&Ovf, 0.0);
					audiodata.TotalreadBufSize = 0;
				}
				else
				{
					// 動作無し
					break;
				}
			}
			// 今回読みこんだ量を保存
			comsize += readsize;

		}
		// 現在の読み込み量を加算
		audiodata.TotalreadBufSize += comsize;
	}

	/// <summary>
	/// バッファーの読み込み(.wav)
	/// </summary>
	/// <param name="buf"></param>
	bool AudioDecoder::BufferDecoderWav(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf)
	{
		// 8bitは考えません
		if (!buf)
		{
			printf("バッファのサイズの確保不足");
			return false;
		}

		// Stereo16bit
		unsigned long readsample = 0;

		readsample = StreamWavDecoder(Format, filename, loopflag, audiodata, buf);

		if (readsample > 0)
		{
			audiodata.NextFirstSample += readsample;
			return true;
		}
		
		printf("サンプルの読み込みに失敗しました\n");
		return false;
	}

	/// <summary>
	/// wavファイルの読み込み
	/// </summary>
	/// <param name="audiodata"></param>
	/// <param name="buf"></param>
	/// <returns></returns>
	unsigned long AudioDecoder::StreamWavDecoder(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf)
	{

		FILE* fp = nullptr;			// ファイルポインタ
		int readsize = 0;
		// ファイルのオープン
		fopen_s(&fp, filename.c_str(), "rb");
		
		if (!fp)
		{
			printf("サウンドファイルの読み取りに失敗しました");
			return 0;
		}

		long samplesize = 0;
		long freadsize = 0;
		int cnt = 0;

		// バッファ読み込み量
		fseek(fp, audiodata.NextFirstSample, SEEK_CUR);

		while (samplesize < audiodata.ReadBufSize)
		{
			freadsize = fread(
				reinterpret_cast<int16_t*>(buf) + cnt,
				Format.Fmt.BlockSize / Format.Fmt.Channels,
				1,
				fp);

			// 読み込めなかった場合の処理
			if (freadsize == 0)
			{
				readsize = samplesize;
				break;
			}

			samplesize += freadsize;
			freadsize = 0;
			cnt++;

		}
		readsize = samplesize;
		

		// 終了処理
		fclose(fp);

		// ループ処理
		if (readsize == 0)
		{
			if (loopflag >= 0)
			{
				// バッファ読み込み終了
				// ループ用に読み込み位置を初期化
				audiodata.NextFirstSample = Format.FirstSampleOffSet;
			}
		}

		return readsize;
	}

	unsigned long AudioDecoder::PreloadWavDecoder(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, void* buf)
	{
		FILE* fp = nullptr;			// ファイルポインタ
		int readsize = 0;
		// ファイルのオープン
		fopen_s(&fp, filename.c_str(), "rb");

		if (!fp)
		{
			printf("サウンドファイルの読み取りに失敗しました");
			return 0;
		}

		long samplesize = 0;
		long freadsize = 0;
		int cnt = 0;

		// バッファ読み込み量
		fseek(fp, audiodata.NextFirstSample, SEEK_CUR);

		// 読み込み終了まで読み込み
		while (1)
		{
			freadsize = fread(
				reinterpret_cast<int16_t*>(buf) + cnt,
				Format.Fmt.BlockSize / Format.Fmt.Channels,
				1,
				fp);

			// 読み込めなかった場合の処理
			if (freadsize <= 0)
			{
				readsize = samplesize;
				break;
			}

			samplesize += freadsize;
			freadsize = 0;
			cnt++;

		}
		readsize = samplesize;

		// 終了処理
		fclose(fp);

		// ループ処理
		if (readsize == 0)
		{
			if (loopflag >= 0)
			{
				// バッファ読み込み終了
				// ループ用に読み込み位置を初期化
				audiodata.NextFirstSample = Format.FirstSampleOffSet;
			}
		}

		return readsize;
	}


}