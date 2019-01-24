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
	bool AudioDecoder::LoadRIFFFormat(AudioResources& source, int soundTypeNumber)
	{

		if (source.Soundtypes[soundTypeNumber].RIFFType == RIFF_WAV)
		{
			return RIFFDecoderWave(filename,format);
		}
		else if (source.Soundtypes[soundTypeNumber].RIFFType == RIFF_OGG)
		{
			return RIFFDecoderOgg(filename,format);
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
			return false;
		}

		vorbis_info* vi = ov_info(&Ovf,-1);

		format.Fmt.FormatType = WAVE_FORMAT_PCM;
		format.Fmt.Channels = vi->channels;
		format.Fmt.SamplesPerSec = vi->rate;
		format.Fmt.BlockSize = vi->channels * 2;
		format.Fmt.BitsPerSample = 16;
		format.Fmt.BytesPerSec = (vi->rate) * (vi->channels * 2);
		// 未使用
		format.DataChunkSample = 0;

		return true;
#endif
		return false;

	}

	bool AudioDecoder::RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format)
	{
		FILE* fp;
		fopen_s(&fp, filename.c_str(), "rb");

		if (fp == NULL)
			return false;

		// RIFFチャンクを読み込み
		fread(format.Riff.RIFFID,1,4,fp);
		fread(&format.Riff.FileSize,4,1,fp);
		fread(format.Riff.WaveFormatType,1,4,fp);

		// FMTチャンクを読み込み
		fread(format.Fmt.FmtID,1,4,fp);
		fread(&format.Fmt.ChunkSize,1,4,fp);
		fread(&format.Fmt.FormatType,2,1,fp);
		fread(&format.Fmt.Channels,2,1,fp);
		fread(&format.Fmt.SamplesPerSec,4,1,fp);
		fread(&format.Fmt.BytesPerSec,4,1,fp);
		fread(&format.Fmt.BlockSize,4,1,fp);
		fread(&format.Fmt.BitsPerSample,2,1,fp);

		// Dataチャンクの読み込み
		fread(format.Data.DataID,1,4,fp);
		fread(&format.Data.DataChunkSize,4,1,fp);

		// データチャンクの開始位置
		format.FirstSampleOffSet = format.Riff.FileSize - format.Data.DataChunkSize;

		fclose(fp);

		return true;

	}

	/// <summary>
	/// オーディオバッファー読み込み用の窓口関数
	/// </summary>
	bool AudioDecoder::AudioBufferDecoder(AudioResources& source, int soundTypeNumber)
	{
		// 使用するバッファの判断
		void* buf;


		// 拡張子の判断
		if (source.Soundtypes[soundTypeNumber].RIFFType == RIFF_WAV)
		{
			BufferDecoderWav(source.Format, source.Data, buf);
			return;
		}
		else if (source.Soundtypes[soundTypeNumber].RIFFType == RIFF_OGG)
		{
			BufferDecoderOgg(source.Data, buf);
			return;
		}

		// 処理なし
		return;
	}

	/// <summary>
	/// バッファーの読み込み(.wav)
	/// </summary>
	/// <param name="buf"></param>
	bool AudioDecoder::BufferDecoderOgg(AudioData& audiodata, void* buf)
	{
		long requestsize = audiodata.ReadBufSize;
		int bitstream = 0;
		int readsize = 0;
		UINT comsize = 0;
		OggVorbis_File Ovf;

		if (ov_fopen(audiodata.PresetSoundName.c_str(), &Ovf))
		{
			// Oggファイルオープンの失敗
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
				if (audiodata.LoopSound == true)
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

	/// <summary>
	/// バッファーの読み込み(.wav)
	/// </summary>
	/// <param name="buf"></param>
	bool AudioDecoder::BufferDecoderWav(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf)
	{
		if (Format.Fmt.Channels == 1)
		{
			Mono16WavDecoder(Format,audiodata,buf);
		}
		else if (Format.Fmt.Channels == 2)
		{
			return false;
			// 現在は無し
		}

		return false;
	}

	/// <summary>
	/// 16bitモノラルで作られているwavファイルの読み込み
	/// </summary>
	/// <param name="audiodata"></param>
	/// <param name="buf"></param>
	/// <returns></returns>
	bool AudioDecoder::Mono16WavDecoder(AUDIOFILEFORMAT& Format,AudioData& audiodata, void* buf)
	{
		// ファイルポインタ
		FILE* fp;

		// ファイルのオープン
		fopen_s(&fp, audiodata.PresetSoundName.c_str(),"rb");

		if (!buf)
			return false;

		if (!fp)
			return false;

		if (audiodata.NextFirstSample >= Format.DataChunkSample)
			return false;

		size_t actualSamples;

		if ((audiodata.NextFirstSample + audiodata.ReadBufSize) > Format.Data.DataChunkSize)
		{
			actualSamples = Format.DataChunkSample - audiodata.NextFirstSample;
		}
		else
		{
			actualSamples = audiodata.ReadBufSize;
		}

		if (fseek(fp, Format.FirstSampleOffSet + audiodata.NextFirstSample*Format.Fmt.BlockSize, SEEK_SET) != 0)
		{
			return false;
		}

		size_t readSample = 0;
		size_t ret = 0;

		while (readSample < actualSamples)
		{
			ret = fread(reinterpret_cast<uint16_t*>(buf) + readSample * Format.Fmt.BlockSize,
				Format.Fmt.BlockSize, actualSamples - readSample, fp);

			if (ret == 0)
				break;

			readSample += ret;
		}

		fclose(fp);

		audiodata.BufferSample = ret * Format.Fmt.BlockSize;


		return readSample;
	}

	//====================================
	//	Data部分の取得
	//	ステレオ読み込みだけど使う予定がないのでこれで
	//	以前の状態を変更かけないでコピーしてきた
	//====================================
	/*std::size_t Streo16WavDecoder(long first, long end, float* left, float* right)
	{
		FILE* fp;

		fopen_s(&fp, m_SoundResouce.PresetSoundName.c_str(), "rb");

		if (!fp)
			return 0;

		if (!m_SoundResouce.HasGotWaveFormat)
			return 0;

		if (first >= m_SoundResouce.DataChunkSample)
			return 0;

		std::size_t actualSamples = first + end > m_SoundResouce.DataChunkSample ? m_SoundResouce.DataChunkSample - first : end;

		if (fseek(fp, m_SoundResouce.firstSampleOffSet + first * m_SoundResouce.Format.nBlockAlign, SEEK_SET) != 0)
			return 0;

		std::size_t readSamples = 0;

		for (; readSamples < actualSamples; ++readSamples)
		{
			// 1 サンプル読み込み
			uint32_t data[2];
			std::size_t ret = fread(data, m_SoundResouce.Format.nBlockAlign, 1, fp);	// Warning: 3 チャンネル以上が来るとバッファオーバーラン
			if (ret == 0) break;

			
			// 16bit signed: -32768...0...32767
			
			int16_t * data_s16 = reinterpret_cast<int16_t *>(data);
			if (m_SoundResouce.Format.nChannels == 1)
			{
				float l = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f :
					static_cast<float>(data_s16[0]) / 32767.0f;
				left[readSamples] = l;
				if (right) right[readSamples] = l;
			}
			else
			{
				float l = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f :
					static_cast<float>(data_s16[0]) / 32767.0f;
				float r = (data_s16[1] < 0) ? static_cast<float>(data_s16[1]) / 32768.0f :
					static_cast<float>(data_s16[1]) / 32767.0f;
				if (right)
				{
					left[readSamples] = l;
					right[readSamples] = r;
				}
				else
				{
					left[readSamples] = (l + r) * 0.5f;
				}
			}
			
			break;
			
		}
		return readSamples;
	}*/

}