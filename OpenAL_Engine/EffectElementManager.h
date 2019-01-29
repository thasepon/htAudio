#pragma once

#include<string>
#include<list>
#include"EffectElementPram.h"

namespace htAudio
{
	class EffectElementManager
	{
	public:
		EffectElementManager();
		~EffectElementManager();

		// EffectParameter�̎擾
		EffectElementPram* GetElementPram(std::string _elementpramname);

	private:
		// �擾�̍ی�����Ȃ������ꍇ�Ɍ������鏈��
		EffectElementPram* SerchExternalFileElementPram();
		// ���������ꍇ�͐V�����v�f��ǉ�����
		EffectElementPram* CreateElementPram();

		std::list<EffectElementPram*> ParameterList; //�|�C���^�����L���Đ��l�����L���܂�

	};
}