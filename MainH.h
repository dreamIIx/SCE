//Autor -dreamIIx
//GitHub - https://github.com/dreamIIx
//Release on GitHub 27.09.2018

#include <iostream>
#include <SFMl/Graphics.hpp>
#include <thread>
#include <mutex>
#include <Windows.h>

#define GETBIT(x,pos)	( ((x) & ( 0x1 << (pos) )) != 0 )

using namespace std;
using namespace sf;

namespace dx
{
	template <typename T>
	class SmartPointer // âûçîâ - drm::SmartPointer<T> example = new T(ëþáîå_÷èñëî);
	{
	private:
		T * ptr;
	public:
		SmartPointer()
			: ptr(nullptr) // àäðåñ åñòü, îáúåêòà íåò(íà êîòîðûé ññûëàåòñÿ óêàçàòåëü)
		{}

		SmartPointer(T *pt)
			: ptr(pt)
		{}

		~SmartPointer()
		{
			delete ptr;
		}

		T& operator*() // âûçîâ - cout << *example << endl; (ñî ñòðîêîâûì òèïîì íå ñðàáîòàåò)
		{
			return *ptr;
		}

		T& operator->()
		{
			return ptr;
		}
	};

	template <typename T>
	class Functor // âûçîâ - drm::Functor<int> example(ëþáîå_÷èñëî);
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

		void operator()() // âûçîâ - example();
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

		Int32 operator*()
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
		static const int MAX = 50;
		Sprite * ptr[MAX];
		bool ready[MAX];
		int last_num = 0;

		SmartPointerArray_Sprite()	{}

		void _reset_visible()
		{
			for (int i = 0; i < last_num; i++)
			{
				ready[i] = true;
			}
		}

		void _reset_from_to(int num1, int num2)
		{
			for (int i = num1 - 1; i <= num2 - 1; i++)
			{
				ready[i] = false;
			}
		}

		inline void _draw_visible(RenderWindow& win)
		{
			for (int i = 0; i < last_num; i++)
			{
				if (ready[i])
				{
					win.draw(*ptr[i]);
					ready[i] = false;
				}
			}
		}

		inline void _draw_from_to(RenderWindow& win, int num1, int num2)
		{
			for (int i = num1 - 1; i < num2; i++)
			{
				if (ready[i])
				{
					win.draw(*ptr[i]);
					ready[i] = false;
				}
			}
		}

		void _delete(int num)
		{
			for (int i = num - 1; i < last_num; i++)
			{
				ptr[i] = ptr[i + 1];
			}
			ptr[last_num - 1] = nullptr;
			ready[last_num - 1] = false;
			last_num--;
		}

		void _insert(Sprite& s, int num)
		{
			for (int i = num - 1; i < last_num; i++)
			{
				ptr[i] = ptr[i + 1];
				ready[i] = true;
			}
			ptr[num - 1] = &s;
			last_num++;
		}
		
		void static_add(Sprite& s)
		{
			ptr[last_num] = &s;
			ready[last_num] = true;
			last_num++;
		}
		
		void _trade(int num1, int num2)
		{
			ptr[last_num] = ptr[num1];
			ptr[num1] = ptr[num2];
			ptr[num2] = ptr[last_num];
			ptr[last_num] = nullptr;
		}
	};

	int randT()
	{
		HCRYPTPROV hProv;
		HCRYPTPROV *phProv = &hProv;

		BYTE Buf1;
		BYTE Buf2;

		BOOL retval;
		retval = CryptAcquireContext(phProv, 0, 0, PROV_RSA_FULL, 0);

		if (retval != 0)
		{
			CryptGenRandom(hProv, DWORD(sizeof(BYTE)), &Buf1);
			CryptReleaseContext(hProv, 0);
		}
		retval = CryptAcquireContext(phProv, 0, 0, PROV_RSA_FULL, 0);

		if (retval != 0)
		{
			CryptGenRandom(hProv, DWORD(sizeof(BYTE)), &Buf2);
			CryptReleaseContext(hProv, 0);
		}

		int i = (int)Buf1;
		i += (int)Buf2;
		//std::cout << i << std::endl;
		return i;
	}

	void bbsort(std::vector<int>& v)
	{
		for (int j = 0; j < v.size() - 1; ++j)
		{
			for (int i = 0; i < v.size() - 1; ++i)
			{
				if (v[i] > v[i + 1])
				{
					int tmp = v[i];
					v[i] = v[i + 1];
					v[i + 1] = tmp;
				}
			}
		}
	}

	/*void radixSort(std::vector<int>& a) {
		int d = 8, w = 32;
		for (int p = 0; p < w / d; p++) {
			std::vector<int> c(1 << d, 0);

			std::vector<int> b = a;
			for (int i = 0; i < a.size(); i++)
				c[(a[i] >> d * p)&((1 << d) - 1)]++;
			for (int i = 1; i < 1 << d; i++)
				c[i] += c[i - 1];
			for (int i = a.size() - 1; i >= 0; i--)
				b[--c[(a[i] >> d * p)&((1 << d) - 1)]] = a[i];
			a = b;
		}
	}*/

	/*int a = 1, b = 100, c = 0;
	for (int j = 31; j >= 0; --j)
	{
		int tmp = 0;
		for (int i = 31; i >= 0; --i)
		{
			tmp = (GETBIT(a, i) & GETBIT(b, j)) == 1 ? ((tmp + 1) << 0x1) : (tmp << 0x1);
		}
		c += (tmp << j);
	}
	std::cout << c * 0.5 << std::endl;*/
	
	/*int a = 1024;

	int shift = static_cast<int>(::std::log2(a)) + 1;

	int x = ~a & ~((~0 >> shift) << shift);
	::std::cout << x << ::std::endl;*/ Inversion bits
};
