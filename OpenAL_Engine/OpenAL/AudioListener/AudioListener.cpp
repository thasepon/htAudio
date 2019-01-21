#include "AudioListener.h"
#include"../AudioFormatData/AudioFormatData.h"

namespace htAudio {

	AudioListener::AudioListener()
	{
	}

	AudioListener::AudioListener(double* Pos, double* Vec, double* Orient)
	{
		*Position = Pos;
		*Velocity = Vec;
		*Pose = Orient;
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::Setposition(double Pos[3])
	{
		Position[0] = &Pos[0];
		Position[1] = &Pos[1];
		Position[2] = &Pos[2];

		ALfloat _pos[3];
		_pos[0] = *Position[0];
		_pos[1] = *Position[1];
		_pos[2] = *Position[3];

		alListenerfv(AL_POSITION, _pos);
	}

	void AudioListener::Setposition(double x, double y, double z)
	{
		Position[0] = &x;
		Position[1] = &y;
		Position[2] = &z;

		ALfloat _pos[3];
		_pos[0] = *Position[0];
		_pos[1] = *Position[1];
		_pos[2] = *Position[3];

		alListenerfv(AL_POSITION,_pos);
	}

	void AudioListener::SetVelocity(double x, double y, double z)
	{
		Velocity[0] = &x;
		Velocity[1] = &y;
		Velocity[2] = &z;

		ALfloat _vec[3];
		_vec[0] = *Velocity[0];
		_vec[1] = *Velocity[1];
		_vec[2] = *Velocity[2];

		alListenerfv(AL_VELOCITY, _vec);
	}

	void AudioListener::SetVelocity(double vec[3])
	{

		Velocity[0] = &vec[0];
		Velocity[1] = &vec[1];
		Velocity[2] = &vec[2];

		ALfloat _vec[3];
		_vec[0] = *Velocity[0];
		_vec[1] = *Velocity[1];
		_vec[2] = *Velocity[2];

		alListenerfv(AL_VELOCITY, _vec);
	}

	void AudioListener::SetOrientation(double AtVec[3], double UpVec[3])
	{

		ALfloat _pose[6];

		Pose[0] = &AtVec[0];
		Pose[1] = &AtVec[1];
		Pose[2] = &AtVec[2];
		Pose[3] = &UpVec[0];
		Pose[4] = &UpVec[1];
		Pose[5] = &UpVec[2];

		_pose[0] = *Pose[0];
		_pose[1] = *Pose[1];
		_pose[2] = *Pose[2];
		_pose[3] = *Pose[3];
		_pose[4] = *Pose[4];
		_pose[5] = *Pose[5];

		alListenerfv(AL_ORIENTATION, _pose);
	}

	void AudioListener::SetOrientation(double Orient[6])
	{
		ALfloat _pose[6];

		Pose[0] = &Orient[0];
		Pose[1] = &Orient[1];
		Pose[2] = &Orient[2];
		Pose[3] = &Orient[3];
		Pose[4] = &Orient[4];
		Pose[5] = &Orient[5];

		_pose[0] = *Pose[0];
		_pose[1] = *Pose[1];
		_pose[2] = *Pose[2];
		_pose[3] = *Pose[3];
		_pose[4] = *Pose[4];
		_pose[5] = *Pose[5];

		alListenerfv(AL_ORIENTATION, _pose);
	}
	
}