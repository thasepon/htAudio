#pragma once

#include<string>

namespace htAudio {

	class EffectElementPram
	{
	public:
		EffectElementPram(uint16_t _id,std::string _name,double _initvalue,double _maxvalue,double _minvalue);
		~EffectElementPram();

		void SetElementValue(double _value);
		double GetElementValue();

		uint16_t GetElementId() { return ElementId; }
		std::string GetElementName() { return ElementName; }

	private:

		uint16_t ElementId;		// Element�̔ԍ�
		std::string ElementName;// �G�������g�̖��O
		double ElementValue;	// �G�t�F�N�g�̌��݂̐��l
		double MaxValue;		// �G�t�F�N�g�̕ϓ��l�̍ő�
		double MinValue;		// �G�t�F�N�g�̕ϓ��l�̍ŏ�

	};

}