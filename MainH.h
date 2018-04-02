#pragma once

#include <iostream>
#include <SFMl/Graphics.hpp>

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
			delete t;
			delete c;
		}

		Int64 operator*()
		{
			*t = c->getElapsedTime();
			return t->asMicroseconds();
		}

		void restart(size_t arg)
		{
			if (arg == 1) c->restart();
		}

		void operator()()
		{
			*t = c->getElapsedTime();
			cout << t->asMicroseconds() << endl;
		}
	private:
		Clock *c = new Clock;
		Time *t = new Time;
	};
};