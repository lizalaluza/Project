#include "string.h"
#include <SFML/Graphics.hpp>
#include <cstdio>

const int window_length = 1920;
const int window_width = 1080;


int main()
{
	setlocale(LC_ALL, "Russian");
	sf::RenderWindow window(sf::VideoMode(window_length, window_width), "HackerTyper", sf::Style::Fullscreen);
	sf::View view = window.getView();

	#pragma warning(disable : 4996) .
	FILE* f = fopen("/home/liza/Desktop/code.txt", "r");
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	rewind(f);
	char* cbuffer = new char[len];
	size_t p = fread(cbuffer, 1, len, f);
	fclose(f);
	String buffer = String(cbuffer).split(p)[0];
	delete[] cbuffer;

	String text;

	sf::Text program;
	sf::Font font;
	if (!font.loadFromFile("/home/liza/Desktop/20016.ttf"))
	{
		std::cout << "error" << std::endl;
	}

	program.setFont(font);
	program.setFillColor(sf::Color(0, 255, 0));
	program.setCharacterSize(25);

	int end = 0;
    int k = 0;

	while (window.isOpen())
	{
		sf::Event event;

		program.setString((buffer.split(end))[0].str);

		window.clear();
		window.setView(view);
		window.draw(program);
		window.display();

		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.key.code == sf::Keyboard::Escape))
			{
				window.close();
				break;
			}

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				view.move(0, -20 * event.mouseWheelScroll.delta);
			}

            if (event.type == sf::Event::TextEntered)
			{
				k += 1;
                if (k > 120 and k < 350)
                {
                    view.move(0, 5);
                }
                else if (k > 350 and k < 630)
                {
                    view.move(0, 3);
                }
			}

			if (event.type == sf::Event::KeyPressed)
			{
				text += String(buffer.str[end] + buffer.str[end + 1]);
				end += 4;
				if (end > p - 5)
					end -= 4;
				break;
			}
		}
	}
	return 0;
}