#include "TXLib.h"
#include "math.h"
#include <cstdlib>
#include "iostream"
#include "string"

const float dt = 0.01;

struct Sphere
{
    int radius;
    int layers;
        int r;
        int g;
        int b;
        float x;
        float y;
        float vx;
        float vy;
    };

void drawSphere(Sphere sphere)
{
    COLORREF a = txGetFillColor();
    txBegin();
    for (int i = 1; i < sphere.layers; i++)
    {
        txSetFillColor(RGB(i * sphere.r / sphere.layers, i * sphere.g /
                           sphere.layers, i * sphere.b / sphere.layers));
        txSetColor(RGB(i * sphere.r / sphere.layers, i * sphere.g /
                       sphere.layers, i * sphere.b / sphere.layers));
        txCircle(sphere.x, sphere.y, sphere.radius - sphere.radius * i /
                                                             sphere.layers);
    }
    txEnd();
    txSetFillColor(a);
    //std::cout << radius;
}

void moveSphere(Sphere* sphere, const float dt)
{
    sphere->x = sphere->x + sphere->vx*dt;
    sphere->y = sphere->y + sphere->vy*dt;
}

void checkCollisionWithWallSphere(Sphere* sphere, const float dt, int width, int height)
{
    if (sphere->x < sphere->radius)
    {
        sphere->x = sphere->radius;
        sphere->vx = - sphere->vx;
    }
    else if (sphere->x > width - sphere->radius)
    {
        sphere->x = width - sphere->radius;
        sphere->vx = - sphere->vx;
    }
    if (sphere->y < sphere->radius)
    {
        sphere->y = sphere->radius;
        sphere->vy = - sphere->vy;
    }
    else if (sphere->y >= height - sphere->radius)
    {
        sphere->y = height - sphere->radius;
        sphere->vy = - sphere->vy;
    }
}

bool isCollisedTwoSpheres(Sphere sphere1, Sphere sphere2, const float dt)
{
    if ((sphere1.x - sphere2.x)*(sphere1.x - sphere2.x) + (sphere1.y - sphere2.y)*
            (sphere1.y - sphere2.y) < (sphere1.radius + sphere2.radius)*
                                        (sphere1.radius + sphere2.radius))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void resolveCollision(Sphere* sphere1, Sphere* sphere2)
{
    float deltax = sphere1->x - sphere2->x;
    float deltay = sphere1->y - sphere2->y;
    float distance = sqrt(deltax*deltax + deltay*deltay);
    if (distance != 0)
    {
        float sumradii = sphere1->radius + sphere2->radius;
        float sin = deltax / distance;
        float cos = deltay / distance;
        float vn1 = sphere1->vx * sin + sphere1->vy * cos;
        float vn2 = sphere2->vx * sin + sphere2->vy * cos;
        float vt1 = sphere1->vx * cos + sphere1->vy * sin;
        float vt2 = sphere2->vx * cos + sphere2->vy * sin;

        float speed = vn2;
        vn2 = vn1;
        vn1 = speed;
        sphere1->x = sphere2->x + sumradii*sin;
        sphere1->y = sphere2->y + sumradii*cos;
        sphere1->vx = vn1 * sin - vt1 * cos;
        sphere1->vy = vn1 * cos + vt1 * sin;
        sphere2->vx = vn2 * sin - vt1 * cos;
        sphere2->vy = vn2 * cos + vt1 * sin;
    }
}

int main()
{
    int width = 800;
    int height = 600;
    int numberofspheres = 200;

    txCreateWindow(width, height);

    txSetFillColor(RGB(0, 0, 0));

    struct Sphere particles[numberofspheres];
    int k = 1;
    int j = 0;
    for (int i = 0; i < numberofspheres; i++)
    {
        particles[i].radius = 3;
        particles[i].x = particles[i].radius*(2*j + 1) + 5*(j + 1);
        particles[i].y = k*(5 + 2*particles[i].radius);
        particles[i].layers = 2;
        particles[i].vx = 30;
        particles[i].vy = 10 + 5*(i/10);
        particles[i].r = 0;
        particles[i].g = 255;
        particles[i].b = 255;
        j += 1;
        if (particles[i].x > width - 3*particles[i].radius - 10)
        {
            k += 1;
            j = 0;
        }
        if (particles[i].y > height - 3*particles[i].radius - 10)
        {
            break;
        }
    }

    while (true)
    {
        txBegin();
        
        txClear();

        for (int i = 0; i < numberofspheres; i++)
        {
            drawSphere(particles[i]);
        }

        txEnd();

        for (int i = 0; i < numberofspheres; i++)
        {
            checkCollisionWithWallSphere(&particles[i], dt, width, height);
        }

        for (int i = 0; i < numberofspheres; i++)
        {
            for (int j = i + 1; j < numberofspheres; j++)
            {
                if (isCollisedTwoSpheres(particles[i], particles[j], dt))
                    {
                        resolveCollision(&particles[i], &particles[j]);
                    }
            }
        }

        for (int i = 0; i < numberofspheres; i++)
        {
            moveSphere(&particles[i], dt);
        }
    }
    return 0;
}

