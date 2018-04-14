#pragma once

#include <iostream>
#include <SFMl/Graphics.hpp>
#include <thread>
#include <mutex>

using namespace std;
using namespace sf;

namespace drm
{
	template <typename T>
	class SmartPointer // вызов - drm::SmartPointer<int> example = new int(любое_число);
	{
	private:
		T * ptr;
	public:
		SmartPointer()
			: ptr(nullptr) // адрес есть, объекта нет(на который ссылается указатель)
		{}

		SmartPointer(T *pt)
			: ptr(pt)
		{}

		~SmartPointer()
		{
			delete ptr;
		}

		T& operator*() // вызов - cout << *example << endl; (со строковым типом не сработает)
		{
			return *ptr;
		}

		T& operator->()
		{
			return ptr;
		}
	};

	template <typename T>
	class Functor // вызов - drm::Functor<int> example(любое_число);
	{
	private:
		T i;
	public:
		Functor()
			: i(NULL)
		{}

		Functor(T type_i)
			: i(type_i)
		{}

		void operator()() // вызов - example();
		{
			cout << i + 10 << endl;
		}
	};

	class TimeGet
	{
	public:
		TimeGet()
		{}

		~TimeGet()
		{
			delete c;
		}

		void restart()
		{
			c->restart();
		}

		float operator*()
		{
			return c->getElapsedTime().asMilliseconds();
		}

		void operator()()
		{
			cout << c->getElapsedTime().asMicroseconds() << endl;
		}
	private:
		Clock *c = new Clock;
	};

	template <typename T>
	class SmartPointerArray
	{
	public:
		SmartPointerArray()
		{

		}

	private:
		T * ptr[num];
	};
};