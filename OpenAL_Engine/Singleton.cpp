#include "Singleton.h"

namespace htAudio
{

	const static int MaxFinalizersSize = 256;
	static int NumFinalizersSize = 0;
	static SingletonFinalizer::FinalizerFunc Finalizers[MaxFinalizersSize];

	void SingletonFinalizer::AddFinalizer(FinalizerFunc func)
	{
		if(NumFinalizersSize < MaxFinalizersSize)
			Finalizers[NumFinalizersSize++] = func;
	}

	void SingletonFinalizer::finalize()
	{
		for (int i = NumFinalizersSize - 1; i >= 0; --i) {
			(*Finalizers[i])();
		}
		NumFinalizersSize = 0;
	}

}