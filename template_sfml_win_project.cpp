/*
debug:
sfml-graphics-s-d.lib
freetype.lib
jpeg.lib
opengl32.lib
sfml-window-s-d.lib
gdi32.lib
sfml-audio-s-d.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib
openal32.lib
sfml-system-s-d.lib
winmm.lib

release:
sfml-graphics-s.lib
freetype.lib
jpeg.lib
opengl32.lib
sfml-window-s.lib
gdi32.lib
sfml-audio-s.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib
openal32.lib
sfml-system-s.lib
winmm.lib
*/

#include <iostream>
#include <thread>
#include <atomic>

#include <Windows.h>

#include "SFML/Graphics.hpp"

constexpr unsigned int def_WIN_X = 1000;
constexpr unsigned int def_WIN_Y = 400;

void mainA(sf::RenderWindow&, sf::View&, volatile ::std::atomic_bool&);

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	sf::RenderWindow win({ def_WIN_X, def_WIN_Y }, "NN");
	win.setVerticalSyncEnabled(true);
	win.setActive(false);
	win.setFramerateLimit(60);

	sf::View view;
	view.reset(sf::FloatRect(0.0f, 0.0f, static_cast<float>(def_WIN_X), static_cast<float>(def_WIN_Y)));

	volatile ::std::atomic_bool isOpen = true;

	::std::thread mainThread(mainA, ::std::ref(win), ::std::ref(view), ::std::ref(isOpen));

	while (isOpen.load())
	{
		sf::Event event;
		while (win.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isOpen.store(false);
				break;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
				{

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{

				}
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
				{

				}
			}
			else if (event.type == sf::Event::Resized)
			{
				view.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y)));
			}
		}
	}

	mainThread.join();
	win.setActive(true);
	win.close();

	return 0;
}

void mainA(sf::RenderWindow& win, sf::View& view, volatile ::std::atomic_bool& is_Open)
{
	win.setActive(true);

	//mA
	while (is_Open.load())
	{

		view.setCenter(static_cast<float>(win.getSize().x / 2), static_cast<float>(win.getSize().y / 2));

		win.clear();
		win.setView(view);
		// draw
		win.display();
	}

	win.setActive(false);
}
