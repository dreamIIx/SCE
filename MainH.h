#pragma once

#include <iostream>
#include <SFMl/Graphics.hpp>

using namespace std;
using namespace sf;

namespace drm
{
	template <typename T>
	class SmartPointer // ����� - drm::SmartPointer<int> example = new int(�����_�����);
	{
	private:
		T * ptr;
	public:

		SmartPointer()
			: ptr(nullptr) // ����� ����, ������� ���(�� ������� ��������� ���������)
		{}

		SmartPointer(T *pt)
			: ptr(pt)
		{}

		~SmartPointer()
		{
			delete ptr;
		}

		T& operator*() // ����� - cout << *example << endl; (�� ��������� ����� �� ���������)
		{
			return *ptr;
		}

		T& operator->()
		{
			return ptr;
		}
	};

	template <typename T>
	class Functor // ����� - drm::Functor<int> example(�����_�����);
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

		void operator()() // ����� - example();
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