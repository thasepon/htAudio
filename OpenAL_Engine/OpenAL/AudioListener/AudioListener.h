#pragma once

#include"../OpenAlCore/OpenALDevice.h"
#include<array>

namespace htAudio {

	/// <summary>
	/// ���X�i�[�̐ݒ蓙������N���X
	/// </summary>
	class AudioListener
	{
	public:
		
		AudioListener();
		AudioListener(double* Pos, double* Vec,double* Orient);
		
		~AudioListener();

		void Setposition(double x, double y, double z);
		void Setposition(double Pos[3]);

		void SetVelocity(double x, double y, double z);
		void SetVelocity(double vec[3]);;

		void SetOrientation(double AtVec[3], double UpVec[3]);
		void SetOrientation(double Orient[6]);

	private:
		double* Position[3];	// �|�W�V����
		double* Velocity[3];	// ����
		double* Pose[6];		// �p��
	};

}