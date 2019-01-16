#pragma once

#include"../OpenAlCore/OpenALDevice.h"
#include<array>

namespace htAudio {

	/// <summary>
	/// ���X�i�[�Ɏg�p����X�e�[�g�Q
	/// �O���t�@�C���֓ǂݍ���/�~�����݂���state������
	/// </summary>
	struct ListenerStates
	{
		float OuterGain;
		float InnerAngle;
		float OuterAngle;
	};

	/// <summary>
	/// ���X�i�[�̐ݒ蓙������N���X
	/// </summary>
	class AudioListener
	{
	public:
		AudioListener();
		~AudioListener();

		void Setposition(float x,float y,float z);
		void Setposition(float Pos[3]);

		void SetVelocity(float x, float y, float z);
		void SetVelocity(float vec[3]);;

		void SetOrientation(float AtVec[3],float UpVec[3]);
		void SetOrientation(float Orient[6]);

		/*void SetConeOuterGain(float angle);
		void SetConeInnerAngle(float angle);
		void SetConeOuterAngle(float angle);
		float GetConeOuterGain();
		float GetConeInnerAngle();
		float GetConeOuterAngle();*/

	private:
		ListenerStates States;
		ALfloat Position[3];
		ALfloat Velocity[3];
		ALfloat Pose[6];

		std::string Path;

	};

}