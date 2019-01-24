#pragma once



#include "../LoadSoundFile.h"
#include"../../OpenAlCore/OpenALDevice.h"

#include"vorbis/vorbisfile.h"
#pragma comment(lib,"libvorbisfile_static.lib")
#pragma comment(lib,"libogg_static.lib")
#pragma comment(lib,"libvorbis_static.lib")

namespace htAudio
{

	//===========================================================
	// TODO
	//	Ogg��ǂݍ��ރN���X
	//	Vorbislib���g�p���Ă��܂��B
	//===========================================================
	class CLoadOgg : public CLoadSoundFile
	{
	public:
		CLoadOgg(std::string soundlistnumb, SoundType xmlinfo, std::string filepath);
		~CLoadOgg();
		void Update();

		void* GetBuffer() {
			if (m_SoundResouce.SubmitTimes == 0)
				return &PrimaryMixed[0];
			else 
				return &SecondMixed[0];
		}

	private:
		std::size_t ReadDataRaw(const std::size_t start, const std::size_t sample, char* buffer);
		void LoadFormat();

		int m_BuffCnt;

		// �Đ��Ɏg�p����o�b�t�@���(Ogg)
		std::vector<char> PrimaryMixed;
		std::vector<char> SecondMixed;

		OggVorbis_File m_Ovf;
		size_t m_TotalReadSize;
	};
}