#include "TXLib.h"
#include <cmath>
#include <cstdlib>
#include "sphere_functions.h"
#include "spring_functions.h"

int main()
{
    int windowx = 1000;
    int windowy = 600;
    int M = 10;
    int F = (M - 1) * M / 2;

    Sphere particles[M];
    int k = 1;
    int j = 0;
    for (int i = 0; i < M; i++)
    {
        particles[i].radius = 30;
        particles[i].x = 200 + particles[i].radius* (2 * j + 1) + 5 * (j + 1);
        particles[i].y = 200 + k * (5 + 2 * particles[i].radius + 30*(i%2));
        particles[i].N = 20;
        particles[i].vx = 0;
        particles[i].vy = 0;
        particles[i].ax = 0;
        particles[i].ay = 0;
        particles[i].r = 0;
        particles[i].g = 255;
        particles[i].b = 255;
        particles[i].m = 10;

        j += 1;
        if (particles[i].x > windowx - 3 * particles[i].radius - 10)
        {
            k += 1;
            j = 0;
        }
        if (particles[i].y > windowy - 3 * particles[i].radius - 10)
        {
            break;
        }
    }

    Spring lines[M][M];

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i != j)
            {
                lines[i][j].k = 40;
                lines[i][j].length = 90;
                //lines[i][j].s1 = &(particles[i]);
            }
            else
            {
                lines[i][j].k = 0;
                lines[i][j].length = 0;
            }
        }
    }

    const double DT = 0.01;
    txCreateWindow(windowx, windowy);
    txSetFillColor(RGB(0, 0, 0));

    while(true)
    {

        txBegin();
        txClear();

        for (int i = 1; i < M; i++)
        {
            draw(particles[i]);
            for (int j = i + 1; j < M; j++)
            {
                drawlines(particles[i], particles[j], lines[i][j]);
            }
        }

        txEnd();

        for (int i = 1; i < M; i++)
        {
            for (int j = i + 1; j < M; j++)
            {
                acc(&(particles[i]), &(particles[j]), lines[i][j]);
            }
        }
        for (int i = 1; i < M; i++)
        {
            speed(&(particles[i]), DT);
            move(&(particles[i]), DT);
            zero_acc(&(particles[i]));
        }

    }
    return 0;

}
