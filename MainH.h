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

	class SmartPointerArray_Sprite
	{
	public:
		Sprite * ptr[20];
		unsigned int last_num = 0;

		SmartPointerArray_Sprite()	{}

		void _draw_visible(RenderWindow& win)
		{
			for (int i = 0; i < last_num; i++)
			{
				win.draw(*ptr[i]);
			}
		}

		void _delete(unsigned int num)
		{
			for (int i = num - 1; i < last_num; i++)
			{
				ptr[i] = ptr[i + 1];
			}
			ptr[last_num - 1] = nullptr;
		}

		void _insert(Sprite* s, unsigned int num)
		{
			for (int i = num - 1; i < last_num; i++)
			{
				ptr[i] = ptr[i + 1];
			}
			ptr[num - 1] = s;
			last_num++;
		}

		void _trade(unsigned int num1, unsigned int num2)
		{
			ptr[last_num] = ptr[num1];
			ptr[num1] = ptr[num2];
			ptr[num2] = ptr[last_num];
			ptr[last_num] = nullptr;
		}
	};
};