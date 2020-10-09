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
    if ((sphere->vx < 0 and sphere->x < sphere->radius - sphere->vx*dt) or (sphere->vx > 0
                                    and sphere->x > width - sphere->radius - sphere->vx*dt))
    {
        sphere->vx = - sphere->vx;
    }
    if ((sphere->vy < 0 and sphere->y < sphere->radius - sphere->vy*dt) or (sphere->vy > 0 and
                                            sphere->y >= height - sphere->radius - sphere->vy*dt))
    {
        sphere->vy = - sphere->vy;
    }
}

bool isCollisedTwoSpheres(Sphere sphere1, Sphere sphere2, const float dt)
{
    float dr = sqrt((sphere1.vx - sphere2.vx)*(sphere1.vx - sphere2.vx) +
                    (sphere1.vy - sphere2.vy)*(sphere1.vy - sphere2.vy));
    if ((sphere1.x - sphere2.x)*(sphere1.x - sphere2.x) + (sphere1.y - sphere2.y)*
            (sphere1.y - sphere2.y) < (sphere1.radius + sphere2.radius + dt*dr)*
                                        (sphere1.radius + sphere2.radius + dt*dr))
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
    float sin = deltax / distance;
    float cos = deltay / distance;
    float vn1 = sphere1->vx * sin + sphere1->vy * cos;
    float vn2 = sphere2->vx * sin + sphere2->vy * cos;
    float vt1 = sphere1->vx * cos + sphere1->vy * sin;
    float vt2 = sphere2->vx * cos + sphere2->vy * sin;

    float speed = vn2;
    vn2 = vn1;
    vn1 = speed;
    sphere1->vx = vn1 * sin - vt1 * cos;
    sphere1->vy = vn1 * cos + vt1 * sin;
    sphere2->vx = vn2 * sin - vt1 * cos;
    sphere2->vy = vn2 * cos + vt1 * sin;
}

int main()
{
    int width = 800;
    int height = 600;
    int numberofspheres = 20;

    txCreateWindow(width, height);

    txSetFillColor(RGB(0, 0, 0));

    struct Sphere particles[numberofspheres];
    for (int i = 0; i < numberofspheres; i++)
    {
        particles[i].x = 50 + 25*i;
        particles[i].y = 50;
        particles[i].radius = 10;
        particles[i].layers = 2;
        particles[i].vx = 100;
        particles[i].vy = 5*i;
        particles[i].r = 255;
        particles[i].g = 0;
        particles[i].b = 0;
    }

    while (true)
    {
        txBegin();

        for (int i = 0; i < numberofspheres; i++)
        {
            drawSphere(particles[i]);
        }

        txEnd();

        txClear();

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

