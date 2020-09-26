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

void checkCollisionSphere(Sphere* sphere)
{
    if (sphere->x <= sphere->radius or sphere->x >= 800 - sphere->radius)
    {
        sphere->vx = - sphere->vx;
    }
    if (sphere->y <= sphere->radius or sphere->y >= 600 - sphere->radius)
    {
        sphere->vy = - sphere->vy;
    }
}

bool isCollisedTwoSpheres(Sphere sphere1, Sphere sphere2)
{
    if ((sphere1.x - sphere2.x)*(sphere1.x - sphere2.x) + (sphere1.y - sphere2.y)*
    (sphere1.y - sphere2.y) <= (sphere1.radius + sphere2.radius)*
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
    txCreateWindow(width, height);

    txSetFillColor(RGB(0, 0, 0));

    double mousex = 0;
    double mousey = 0;
    double mouseOldx = 0;
    double mouseOldy = 0;

    Sphere sphere1 = {50, 100, 255, 0, 0, 100, 100, 800, 300};
    Sphere sphere2 = {50, 100, 0, 255, 0, 250, 250, 300, 300};
    Sphere sphere3 = {50, 100, 0, 0, 255, 400, 400, 300, 300};

    int points = 0;
    std::cout << "Цель - догонять синий шар и убегать от зеленого";
    std::cout << "\n";
    std::cout << "Очки: 0";
    std::cout << "\n";

    while (points*points < 100)
    {
        mouseOldx = mousex;
        mouseOldy = mousey;
        mousex = txMouseX();
        mousey = txMouseY();

        if (txMouseButtons() > 0 )
        {
            float deltax2 = mousex - sphere2.x;
            float deltay2 = mousey - sphere2.y;
            float distance2 = sqrt(deltax2*deltax2 + deltay2*deltay2);
            float deltax3 = mousex - sphere3.x;
            float deltay3 = mousey - sphere3.y;
            float distance3 = sqrt(deltax3*deltax3 + deltay3*deltay3);

            if (distance2 >= sphere1.radius + sphere2.radius and distance3 >=
            sphere1.radius + sphere3.radius and mousex > sphere1.radius and
            mousex < width - sphere1.radius and mousey > sphere1.radius and
            mousey < height - sphere1.radius)
            {
                sphere1.x = mousex;
                sphere1.y = mousey;
                sphere1.vx = (mousex - mouseOldx) / 10/ dt;
                sphere1.vy = (mousey - mouseOldy) / 10/ dt;
            }
        }

        txBegin();

        drawSphere(sphere1);
        drawSphere(sphere2);
        drawSphere(sphere3);

        txEnd();

        txClear();

        checkCollisionSphere(&sphere1);
        checkCollisionSphere(&sphere2);
        checkCollisionSphere(&sphere3);

        bool collisionResult12 = isCollisedTwoSpheres(sphere1, sphere2);
        if (collisionResult12)
        {
            resolveCollision(&sphere1, &sphere2);
            points -= 1;
            std::cout << "Очки: ";
            std::cout << points;
            std::cout << "\n";
        }
        bool collisionResult13 = isCollisedTwoSpheres(sphere1, sphere3);
        if (collisionResult13)
        {
            resolveCollision(&sphere1, &sphere3);
            points += 1;
            std::cout << "Очки: ";
            std::cout << points;
            std::cout << "\n";
        }
        bool collisionResult23 = isCollisedTwoSpheres(sphere2, sphere3);
        if (collisionResult23)
        {
            resolveCollision(&sphere2, &sphere3);
        }

        moveSphere(&sphere1, dt);
        moveSphere(&sphere2, dt);
        moveSphere(&sphere3, dt);

    }
    if (points < 0)
    {
        std::cout << "LOSE";
    }
    else
    {
        std::cout << "WIN";
    }
    return 0;
}
