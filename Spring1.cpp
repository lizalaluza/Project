#include "TXLib.h"
#include <cmath>
#include <cstdlib>
#include "functions1.h"

int main()
{
    int windowx = 1000;
    int windowy = 600;
    int M = 4;
    int F = (M - 1) * M / 2;

    Sphere[] particles = new Sphere(M);
    int k = 1;
    int j = 0;
    for (int i = 0; i < M; i++)
    {
        particles[i] = new particles();
        particles {30, 30 * (2 * j + 1) + 5 * (j + 1), k * (5 + 2 * 30 + 30 * (i % 2)), 20, 0, 0, 0, 0, 255, 0, 0, 1000};

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

    //Spring lines[M][M];
    for (int i = 0; i < M; i++ )
    {
        for (int j = 0; j < M; j++ )
        {
            if (i != j)
            {
                Spring lines[i][j] {4, 10};
            }

            else
            {
                Spring lines[i][j] {0, 0};
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
            particles[i].draw();
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
                acc(particles[i], particles[j], lines[i][j])
            }
        }

        for (int i = 1; i < M; i++)
        {
            particles[i].speed();
            particles[i].move();
            particles[i].zero_acc();
        }

        for (int i = 1; i < M; i++)
        {
            particles[i].checkCollision();
        }

    }
    return 0;

}
