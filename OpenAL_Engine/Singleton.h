#pragma once
#include <iostream>
#include <thread>
#include <mutex>

namespace htAudio
{
	class SingletonFinalizer
	{
	public:
		typedef void(*FinalizerFunc)();
		static void AddFinalizer(FinalizerFunc func);
		static void finalize();
	};

	template<typename T>
	class Singleton final
	{
	public:

		static T* get_Instance()
		{
			std::call_once(initflag, Create);
			return instance;
		}

	private:
		static void Create()
		{
			instance = new T;
			SingletonFinalizer::AddFinalizer(&Singleton<T>::Destroy);
		}

		static void Destroy()
		{
			delete instance;
			instance = nullptr;
		}

		static std::once_flag initflag;
		static T* instance;

	};

	template <typename T> std::once_flag Singleton<T>::initflag;
	template <typename T> T* Singleton<T>::instance = nullptr;
}