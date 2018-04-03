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
			delete c;
		}

		void restart()
		{
			c->restart();
		}

		Int64 operator*()
		{
			return c->getElapsedTime().asMicroseconds();
		}

		void operator()()
		{
			cout << c->getElapsedTime().asMicroseconds() << endl;
		}
	private:
		Clock *c = new Clock;
	};

	class CreateSpriteT
	{
	public:
		Sprite * object = new Sprite;

		CreateSpriteT(Texture& t)
		{
			object->setTexture(t);
		}

		~CreateSpriteT()
		{
			delete object;
		}

		void reset(int x1, int x2, int y1, int y2)
		{
			object->setTextureRect(IntRect(x1, y1, x2, y2));
		}

		Sprite operator()()
		{
			return *object;
		}
	};
};