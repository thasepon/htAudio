#pragma once

namespace htAudio
{
	class AudioOrder
	{
	public:
		~AudioOrder();
		void SetOrder(int source) {};
		void SetOrder(int source, int latency) {};

	private:
	};

}