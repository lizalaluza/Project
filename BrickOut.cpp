#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "bricks.h"
#define ARRAYDOUBLE_H


int main()
{
    float windowx = 1300;
    float windowy = 800;
    float radius = 10;
    float vx = 60;
    float vy = -50;
    float sticklx = 160;
    float stickly = 7; 
    float stickx = windowx / 2 - sticklx / 2;
    float sticky = windowy - (50 + stickly);
    int gamestate = 1; 

    Brick bricks[40];
    int k = 1;
    int j = 0;
    int m = 0;
    for (int i = 0; i < 40; i++)
    {
        m = k % 2;
        bricks[i].exist = true;
        bricks[i].x = 250 - 40 * m + 83 * j;
        bricks[i].y = 100 + 35 * k;
        j += 1;
        if (j >= 10)
            {
                j = 0;
                k += 1;
            }
    }

    /*bool array[40];
    for (int i=0; i < 40; i++)
    {
        array[i] = true;
    }*/
    
    float y = windowy - (50 + stickly + 2 * radius);
    float x = windowx / 2 - radius;

    sf::RenderWindow window(sf::VideoMode(windowx, windowy), "UwU");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ x, y });

    sf::RectangleShape rectangle(sf::Vector2f(160.f, 7.f));
    rectangle.setPosition({ stickx, sticky });
    rectangle.setFillColor(sf::Color::Blue); 

    sf::RectangleShape rectangle1(sf::Vector2f(80.f, 30.f));
    rectangle1.setPosition({ stickx, sticky });
    rectangle1.setFillColor(sf::Color::Red);

    while (gamestate == 1)
    {
        window.clear();
        shape.setPosition({ x, y });
        rectangle.setPosition({ stickx, sticky });
        window.draw(rectangle);
        window.draw(shape);
        for (int i = 0; i < 40; i++)
        {   
            rectangle1.setPosition({ bricks[i].x, bricks[i].y });
            if (bricks[i].exist)
            {
                window.draw(rectangle1);    
            }
        }
        checkCollision(&x, &vx, &y, &vy, windowx, windowy, radius);
        collisionTablet(stickx, sticky, sticklx, x, y, &vy, radius, DT);
        for (int i = 0; i < 40; i++)
        {
            brickCollision(x, y, &vx, &vy, radius, DT, &bricks[i]);
        }
        circleMove(&x, vx, &y, vy);
        float mousex = sf::Mouse::getPosition(window).x;

        if (mousex <= (windowx - sticklx / 2 ) and mousex >= (sticklx / 2))
        {
            stickx = mousex - sticklx / 2;
        }
        
        
        window.display();
        if (y >= 780)
        {
            window.clear();
            gamestate = 2;
        }

        int q = 0;
        for (int i = 0; i < 40; i++)
        {
            if ( bricks[i].exist == false)
            {
               q += 1;
            }

            else
            {
                break;
            }

            if (q == 40)
            {
                window.clear();
                gamestate = 3;
            }
        }  
    }

    if (gamestate == 2)
    {
        sf::Texture t;
        t.loadFromFile("lose.jpg");
        sf::Sprite s;
        s.setTexture(t);
        s.setPosition(100, 250 );

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            window.draw(s);
            window.display();
        }
    }

    if (gamestate == 3)
    {
        sf::Texture t;
        t.loadFromFile("win.jpg");
        sf::Sprite s;
        s.setTexture(t);
        s.setPosition(100, 250);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            window.draw(s);
            window.display();
        }
        
    }
    return 0;
}
