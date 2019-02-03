#pragma once

class AudioManager;

namespace htAudio
{
	class AudioOrder
	{
	public:
		~AudioOrder();
		void SetOrder(AudioManager* ptr, int source) {};
		void SetOrder(AudioManager* ptr, int source, int latency) {};

	private:
	};

}