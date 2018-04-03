#include <iostream>
#include <Windows.h>
#include <SFMl/Graphics.hpp>
#include <thread>
#include <mutex>
#include "MainH.h"

using namespace std;
using namespace sf;

mutex mm;

void thread2()
{
	int j = 1;
	int jy;

	while (true)
	{
		j++;
		jy = mm.try_lock();
		if (jy == 1)
		{
			cout << j << endl;
			mm.unlock();
		}
	}
}

void thread1()
{
	int i = 0;
	int d;

	while (true)
	{
		d = mm.try_lock();
		if (d == 1)
		{
			while (i != 1)
			{
				cin >> i;
			}
			mm.unlock();
			i = 0;
		}
	}
}

int main()
{
	thread maint1(thread1);
	thread maint2(thread2);

	maint1.detach();
	maint2.join();

	return 0;
}