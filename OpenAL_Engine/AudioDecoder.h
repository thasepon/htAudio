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
		AudioDecoder();		// �R���X�g���N�^
		~AudioDecoder();	// �f�X�g���N�^

		static bool LoadRIFFFormat(std::string filename, RIFFType type, AUDIOFILEFORMAT& format);		// �t�@�C���t�H�[�}�b�g�̎擾		
		static bool AudioBufferDecoder(AUDIOFILEFORMAT& Format, AudioData& audiodata, RIFFType type,void* buf);	// �t�@�C���̃o�b�t�@�[���擾

	private:

		static bool RIFFDecoderOgg(std::string filename, AUDIOFILEFORMAT& format);
		static bool RIFFDecoderWave(std::string filename, AUDIOFILEFORMAT& format);

		static bool BufferDecoderOgg(AudioData& audiodata, void* buf);	// �I�[�f�B�I�o�b�t�@�[�̎擾(.wav)
		static bool BufferDecoderWav(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf); // �I�[�f�B�I�o�b�t�@�[�̎擾(.ogg)

		static bool Mono16WavDecoder(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf);
		// �K�v�ɂȂ�����������܂��B
		//static bool Streo16WavDecoder(AUDIOFILEFORMAT& Format, AudioData& audiodata, void* buf);
	};

}