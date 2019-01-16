#include "OpenALDevice.h"

#include<stdio.h>
namespace htAudio {
	OpenALDevice::OpenALDevice()
	{
		// OpenAL�̏�����
		printf("���������܂���\n");
		Device = alcOpenDevice(nullptr);
		
		if( alcIsExtensionPresent(Device, "ALC_EXT_EFX") == AL_FALSE)
		{
			printf("alcIsExtensionPresent�̐ݒ�Ɏ��s���܂���");
			CreateDevice = false;
		}
		
		ALint Attribs[4] = { 0 };
		Attribs[0] = ALC_MAX_AUXILIARY_SENDS;
		Attribs[1] = 4;

		Context = alcCreateContext(Device, Attribs);

		ALCboolean success = alcMakeContextCurrent(Context);

		if (success == false)
		{
			printf("alcMakeContextCurrent�Ɏ��s���܂���");
			CreateDevice = false;
		}

		alcGetIntegerv(Device, ALC_MAX_AUXILIARY_SENDS, 1, &Sends);
		CreateDevice = true;

	}
	
	OpenALDevice::~OpenALDevice()
	{
		printf("OpenAL��������܂�\n");
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(Context);
		alcCloseDevice(Device);
	}
	
	void OpenALDevice::ErrorFunction()
	{
		ALCenum err;
		err = alcGetError(Device);

		switch (err)
		{
		case AlutError::ALUT_ERROR_NO_ERROR:
			printf("�G���[�Ȃ�\n");
			break;

		case AlutError::ALUT_ERROR_OUT_OF_MEMORY:
			printf("�������s���ł�\n");
			break;

		case AlutError::ALUT_ERROR_INVALID_ENUM:
			printf("ALUT�̊֐��ɕs���Ȓ萔���^�����܂���\n");
			break;

		case AlutError::ALUT_ERROR_INVALID_VALUE:
			printf("ALUT�̊֐��ɕs���Ȓl���^�����܂���\n");
			break;

		case AlutError::ALUT_ERROR_INVALID_OPERATION:
			printf("�s�������삪�s���ł�\n");
			break;

		case AlutError::ALUT_ERROR_NO_CURRENT_CONTEXT:
			printf("�R���e�L�X�g���Z�b�g����Ă܂���\n");
			break;

		case AlutError::ALUT_ERROR_AL_ERROR_ON_ENTRY:
			printf("ALUT�̃G���g���[�G���[\n");
			break;

		case AlutError::ALUT_ERROR_ALC_ERROR_ON_ENTRY:
			printf("ALUT�̃G���g���[�G���[\n");
			break;

		case AlutError::ALUT_ERROR_OPEN_DEVICE:
			printf("�f�o�C�X�I�[�v���̍ۂɃG���[���������܂���\n");
			break;

		case AlutError::ALUT_ERROR_CLOSE_DEVICE:
			printf("�f�o�C�X�N���[�Y�̍ۂɃG���[���������܂���\n");
			break;

		case AlutError::ALUT_ERROR_CREATE_CONTEXT:
			printf("�R���e�L�X�g�����ŃG���[���������܂���\n");
			break;

		case AlutError::ALUT_ERROR_MAKE_CONTEXT_CURRENT:
			printf("�R���e�L�X�g�̕ύX���o���܂���ł���\n");
			break;

		case AlutError::ALUT_ERROR_DESTROY_CONTEXT:
			printf("�R���e�L�X�g�̔j�󂪏o���܂���ł���\n");
			break;

		case AlutError::ALUT_ERROR_GEN_BUFFERS:
			printf("ALBuffer�𐶐�����ۂɃG���[���������܂���");
			break;

		case AlutError::ALUT_ERROR_BUFFER_DATA:
			printf("ALBuffer�𑗐M����ۂɃG���[���������܂���");
			break;

		case AlutError::ALUT_ERROR_IO_ERROR:
			printf("I/O�G���[\n");
			break;

		case AlutError::ALUT_ERROR_UNSUPPORTED_FILE_TYPE:
			printf("�T�|�[�g����Ă��Ȃ��t�@�C���^�C�v�ł�\n");
			break;

		case AlutError::ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE:
			printf("�T�|�[�g����Ă��Ȃ����[�h�ł�\n");
			break;

		case AlutError::ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA:
			printf("�T�E���h�f�[�^�ɖ�肪����܂�\n");
			break;

		}
	}
}