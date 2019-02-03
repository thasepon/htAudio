#include "Cone.h"

namespace htAudio
{

	Cone::Cone(ALuint source)
	{
		Source = source;
	}


	Cone::~Cone()
	{
	}


	void Cone::SetConeOuterGain(float val)
	{
		ConeOuterGain = val;
		alSourcef(Source, AL_CONE_OUTER_GAIN, ConeOuterGain);
	}

	float Cone::GetConeOuterGain()
	{
		alGetSourcef(Source, AL_CONE_OUTER_GAIN, &ConeOuterGain);
		return ConeOuterGain;
	}

	void Cone::SetConeInnerAngle(float val)
	{
		InnerAngle = val;
		alSourcef(Source, AL_CONE_INNER_ANGLE, InnerAngle);
	}

	float Cone::GetConeInnerAngle()
	{
		alGetSourcef(Source, AL_CONE_INNER_ANGLE, &InnerAngle);
		return InnerAngle;
	}

	void Cone::SetConeOuterAngle(float val)
	{
		OuterAngle = val;
		alSourcef(Source, AL_CONE_OUTER_ANGLE, OuterAngle);
	}

	float Cone::GetConeOuterAngle()
	{
		alGetSourcef(Source, AL_CONE_OUTER_ANGLE, &OuterAngle);
		return OuterAngle;
	}


}