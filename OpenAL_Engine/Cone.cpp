#include "Cone.h"
#include"OpenAL\AudioFormatData\AudioFormatData.h"


namespace htAudio
{

	Cone::Cone(ALuint source, std::string elementjsonname)
	{
		Source = source;
		AudioFormatData::LoadEffectData(Info, elementjsonname);
	}


	Cone::~Cone()
	{
	}


	void Cone::SetConeOuterGain(float val)
	{
		Info.ConeOuterGain = val;
		alSourcef(Source, AL_CONE_OUTER_GAIN, Info.ConeOuterGain);
	}

	float Cone::GetConeOuterGain()
	{
		ALfloat getval;
		alGetSourcef(Source, AL_CONE_OUTER_GAIN, &getval);
		return getval;
	}

	void Cone::SetConeInnerAngle(float val)
	{
		Info.InnerAngle = val;
		alSourcef(Source, AL_CONE_INNER_ANGLE, Info.InnerAngle);
	}

	float Cone::GetConeInnerAngle()
	{
		ALfloat getval;
		alGetSourcef(Source, AL_CONE_INNER_ANGLE, &getval);
		return Info.InnerAngle;
	}

	void Cone::SetConeOuterAngle(float val)
	{
		Info.OuterAngle = val;
		alSourcef(Source, AL_CONE_OUTER_ANGLE, Info.OuterAngle);
	}

	float Cone::GetConeOuterAngle()
	{
		ALfloat getval;
		alGetSourcef(Source, AL_CONE_OUTER_ANGLE, &getval);
		return getval;
	}


}