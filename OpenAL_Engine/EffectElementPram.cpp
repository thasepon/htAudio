#include "EffectElementPram.h"


namespace htAudio {

	/// <summary>
	/// î•ñ‚Ì”’l‚ğİ’è
	/// </summary>
	/// <param name="_id"></param>
	/// <param name="_name"></param>
	/// <param name="_initvalue"></param>
	/// <param name="_maxvalue"></param>
	/// <param name="_minvalue"></param>
	EffectElementPram::EffectElementPram(uint16_t _id, std::string _name, double _initvalue, double _maxvalue, double _minvalue)
	{
		ElementId = _id;
		ElementName = _name;
		ElementValue = _initvalue;
		MaxValue = _maxvalue;
		MinValue = _minvalue;
	}

	EffectElementPram::~EffectElementPram()
	{
	}

	void EffectElementPram::SetElementValue(double _value)
	{
		if (_value >= MaxValue)
			_value = MaxValue;

		if (_value <= MinValue)
			_value = MinValue;

		ElementValue = _value;

	}

	double EffectElementPram::GetElementValue()
	{
		return ElementValue;
	}

}