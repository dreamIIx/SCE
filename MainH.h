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