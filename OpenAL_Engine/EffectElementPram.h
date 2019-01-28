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

	private:

		uint16_t ElementId;		// Elementの番号
		std::string ElementName;// エレメントの名前
		double ElementValue;	// エフェクトの現在の数値
		double MaxValue;		// エフェクトの変動値の最大
		double MinValue;		// エフェクトの変動値の最小

	};

}