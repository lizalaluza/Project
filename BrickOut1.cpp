#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "bricks.h"
#define ARRAYDOUBLE_H


int main()
{
    float windowx = 1000;
    float windowy = 800;
    float radius = 10;
    float vx = 50;
    float vy = -50;
    float sticklx = 100;
    float stickly = 10;
    float stickx = windowx / 2 - sticklx / 2;
    float sticky = windowy - (50 + stickly);

    int array[40];
    array[0] = {1};
    array[1] = {1};
    array[2] = {1};
    array[3] = {1};
    array[4] = {1};
    array[5] = {1};
    array[6] = {1};
    array[7] = {1};
    array[8] = {1};
    array[9] = {1};
    array[10] = {1};
    array[11] = {1};
    array[12] = {1};
    array[13] = {1};
    array[14] = {1};
    array[15] = {1};
    array[16] = {1};
    array[17] = {1};
    array[18] = {1};
    array[19] = {1};
    array[20] = {1};
    array[21] = {1};
    array[22] = {1};
    array[23] = {1};
    array[24] = {1};
    array[25] = {1};
    array[26] = {1};
    array[27] = {1};
    array[28] = {1};
    array[29] = {1};
    array[30] = {1};
    array[31] = {1};
    array[32] = {1};
    array[33] = {1};
    array[34] = {1};
    array[35] = {1};
    array[36] = {1};
    array[37] = {1};
    array[38] = {1};
    array[39] = {1};
    array[40] = {1};


    float y = windowy - (50 + stickly + 2 * radius);
    float x = windowx / 2 - radius;

    sf::RenderWindow window(sf::VideoMode(windowx, windowy), "UwU");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ x, y });

    sf::RectangleShape rectangle(sf::Vector2f(100.f, 10.f));
    rectangle.setPosition({ stickx, sticky });
    rectangle.setFillColor(sf::Color::Blue);

    sf::RectangleShape rectangle1(sf::Vector2f(80.f, 30.f));
    rectangle1.setPosition({ stickx, sticky });
    rectangle1.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        shape.setPosition({ x, y });
        rectangle.setPosition({ stickx, sticky });
        window.draw(rectangle);
        window.draw(shape);
        int k = 0;
        int j = 0;
        int m = 0;
        for (int i = 0; i < 40; i++)
        {
            m = k % 2;
            rectangle1.setPosition({ 100 - 40 * m + 83 * j, 100 + 35 * k });
            if (array[i] == 1)
            {
                window.draw(rectangle1);
            }

            j += 1;
            if (j >= 10)
            {
                j = 0;
                k += 1;
            }

        }
        checkCollision(&x, &vx, &y, &vy, windowx, windowy, radius);
        collisionTablet(stickx, sticky, sticklx, x, y, &vy, radius, DT);
        brickCollision(x, y, &vx, &vy, radius, DT, array);
        circleMove(&x, vx, &y, vy);
        float mousex = sf::Mouse::getPosition(window).x;

        if (mousex <= (windowx - sticklx / 2 ) and mousex >= (sticklx / 2))
        {
            stickx = mousex - sticklx / 2;
        }


        window.display();
        if (y >= 780)
        {
            window.close();
            array[40] = {2};
            break;
        }

        int q = 0;
        for (int i = 0; i < 41; i++)
        {
            if (array[i] == 0)
            {
               q += 1;
            }

            else if (q != 40)
            {
                break;
            }

            else if (q == 40)
            {
                window.close();
                array[40] = {3};
                break;
            }
        }
    }

    if (array[40] == 2)
    {
        sf::RenderWindow window1(sf::VideoMode(windowx, windowy), "UwU");
        sf::Texture t;
        t.loadFromFile("ya4.jpg");
        sf::Sprite s;
        s.setTexture(t);
        s.setPosition(0, 100 );

        while (window1.isOpen())
        {
            sf::Event event;
            while (window1.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window1.close();
            }
            window1.clear();
            window1.draw(s);
            window1.display();
        }
    }

    if (array[40] == 3)
    {
        sf::RenderWindow window1(sf::VideoMode(windowx, windowy), "UwU");
        sf::Texture t;
        t.loadFromFile("33.jpg");
        sf::Sprite s;
        s.setTexture(t);
        s.setPosition(0, 0);

        while (window1.isOpen())
        {
            sf::Event event;
            while (window1.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window1.close();
            }
            window1.clear();
            window1.draw(s);
            window1.display();
        }

    }
    return 0;
}
