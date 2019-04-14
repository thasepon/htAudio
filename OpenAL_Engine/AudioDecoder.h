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
	/// 16bitWav������Ogg�̃f�R�[�_�[
	/// </summary>
	class AudioDecoder
	{
	public:
		~AudioDecoder();	// �f�X�g���N�^

		static bool LoadRIFFFormat(AUDIOFILEFORMAT& headerfmt,SoundType audiodata,std::string filepath);		// �t�@�C���t�H�[�}�b�g�̎擾		
		static bool AudioBufferDecoder(void* buf, AudioData& audiodata,SoundType type, AUDIOFILEFORMAT headerfmt, std::string filepath);	// �t�@�C���̃o�b�t�@�[���擾

	private:
		AudioDecoder();		// �R���X�g���N�^

		// header�����̃f�R�[�_�[
		static bool RIFFDecoderOgg(std::string filename, AUDIOFILEFORMAT& format);
		static bool RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format);

		// Data�����̃f�R�[�_�[
		static bool BufferDecoderOgg(AudioData& audiodata, std::string filename,bool loopflag, void* buf);	// �I�[�f�B�I�o�b�t�@�[�̎擾(.wav)
		static bool BufferDecoderWav(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf); // �I�[�f�B�I�o�b�t�@�[�̎擾(.ogg)

		static unsigned long StreamWavDecoder(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf);
		static unsigned long PreloadWavBuffer(AUDIOFILEFORMAT Format, std::string filename, bool loopflag, AudioData& audiodata, void* buf);

		static void PCM16bitDecoder(void* buf,int& readsize, AUDIOFILEFORMAT fmt, AudioData& audiodata, FILE* fp);
		
	};

}