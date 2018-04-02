#pragma once
#include <iostream>

namespace drm
{
	template <typename T>
	class SmartPointer
	{
	public:

		SmartPointer(T *pt)
			: ptr(pt)
		{}

		SmartPointer()
			: ptr(nullptr) // адрес есть, объекта нет(на который ссылается указатель)
		{}

		~SmartPointer()
		{
			delete ptr;
		}

		T& operator*()
		{
			return *ptr;
		}

		T& operator->()
		{
			return ptr;
		}

	private:
		T *ptr;
	};
};