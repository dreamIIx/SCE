#pragma once
#include <iostream>

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
};